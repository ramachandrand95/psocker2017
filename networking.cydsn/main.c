/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

typedef enum state {idleState, collisionState, busyState} State;

State systemState = idleState;

_Bool lowFlag = 0;

//period and counter for timer
#define COLL_PERIOD     52
#define COLL_COUNTER    51
#define IDLE_PERIOD     830
#define IDLE_COUNTER    829
//transmit timer stuff
#define TX_PERIOD     50 //gives 0.50ms or 500us for unipolar-rz at 1000bps
#define TX_COUNTER    49
//serial buffer size
#define SERIAL_BUFFER_SIZE 500
//serial buffer
unsigned char SERIAL_BUFFER[SERIAL_BUFFER_SIZE];
int SERIAL_POS = 0;
//flag to determine if the UART is connected
int uartConnected = 0;
//data cache for later use
unsigned char CONVERTED_DATA[SERIAL_BUFFER_SIZE][16];
int dataConvertedReadOutCount = 0;
char currentChar;
int dataSize;
int TX_Bit_Counter = 0; //keeps track of what would be a for loop in the ISR
int count = 0; //keeps track of which bit we're on

CY_ISR(Timer_TX_ISR_HANDLER)
{
	Timer_TX_STATUS; //clear TX timer
	//get data
	currentChar = SERIAL_BUFFER[SERIAL_POS];

	if(SERIAL_POS < dataSize){ 
	//encode into Unipolar-RZ
	
	//Data to be transmitted. This represents one byte of data and will
	//be encoded in unipolar RZ. For every bit there will be 2 bits, and there are 8 bits
	
		if(TX_Bit_Counter == 0){
			TX_Write(1);
			CONVERTED_DATA[SERIAL_POS][TX_Bit_Counter] = 0x31;
		}else if(TX_Bit_Counter%2 != 0){
			TX_Write(0);
			CONVERTED_DATA[SERIAL_POS][TX_Bit_Counter] = 0x30;
		}else{
			//see if a 1 exists at the bit of the char, otherwise write a 0 out
			//this should transmit MSB first
			if(currentChar & (1<<(6-count))){
				TX_Write(1);
				CONVERTED_DATA[SERIAL_POS][TX_Bit_Counter] = 0x31;
			}else{
				TX_Write(0);
				CONVERTED_DATA[SERIAL_POS][TX_Bit_Counter] = 0x30;   
			}
				++count;
		}
        ++TX_Bit_Counter;
        if(TX_Bit_Counter >= 16){
		    ++SERIAL_POS;
		    count = 0;
		    TX_Bit_Counter = 0;
        }
 
  }
	

}

CY_ISR(TIMER)
{
   	Timer_1_STATUS; //clear timer
    
    if (!(lowFlag) ){
        systemState = idleState;
    } else {
        systemState = collisionState;
    }
}

CY_ISR(RISING)
{
    if ((!lowFlag)){
        Timer_1_WritePeriod(COLL_PERIOD);
        Timer_1_WriteCounter(COLL_COUNTER);
        Timer_1_Start();
        lowFlag = 1;
        systemState = busyState;
    }
}
 
CY_ISR(FALLING)
{
    if (lowFlag){
        Timer_1_WritePeriod(IDLE_PERIOD);
        Timer_1_WriteCounter(IDLE_COUNTER);
        Timer_1_Start();
        lowFlag = 0;
        systemState = busyState;
    }
}

int main(void)
{
    CyGlobalIntEnable;
    TimerISR_StartEx(TIMER);
    INT_RISING_StartEx(RISING);
    INT_FALLING_StartEx(FALLING);
    
    Timer_TX_WritePeriod(TX_PERIOD);
    Timer_TX_WriteCounter(TX_COUNTER);
    Timer_TX_ISR_StartEx(Timer_TX_ISR_HANDLER);
    Timer_TX_Start();
    
    UART_Start(UART_device,UART_5V_OPERATION);

    while(1){
         //check if UART is connected, then set flag
		if(UART_GetDTERate() == 57600){
			uartConnected = 1;
		}
	
		//Host can send double SET_INTERFACE request, which sounds sub-optimal for us if we don't handle that
		if (0 != UART_IsConfigurationChanged())
		{
			//re-initialize device
			if (0 != UART_GetConfiguration())
			{
				//Enumeration is done, allow receieving data from host
				UART_CDC_Init();
			}
		}
                
        //check if the UART has data, then place in buffer
        if(UART_DataIsReady() != 0){
            dataSize = UART_GetAll(SERIAL_BUFFER);
            while(!UART_CDCIsReady());
            UART_PutCRLF();
            dataConvertedReadOutCount = 0;            
            SERIAL_POS = 0;
        }
        //write converted data to UART

        if(UART_CDCIsReady() != 0){
            if(dataConvertedReadOutCount < dataSize && SERIAL_POS == dataSize){
                for(int y = 0; y < 16; y++){
                 while(!UART_CDCIsReady());
                 UART_PutChar(CONVERTED_DATA[dataConvertedReadOutCount][y]); 
                }
                ++dataConvertedReadOutCount;
                while(!UART_CDCIsReady());
                UART_PutCRLF();
            }
        }
        
        switch(systemState){
            //idle state
            case idleState :;
                IDLE_Write(1);
                BUSY_Write(!IDLE_Read());
                COLLISION_Write(!IDLE_Read());
            break;
            //busy state
            case busyState:
                BUSY_Write(1);
                IDLE_Write(!BUSY_Read());
                COLLISION_Write(!BUSY_Read());
            break;
            //collision state
            case collisionState:;
                COLLISION_Write(1);
                IDLE_Write(!COLLISION_Read());
                BUSY_Write(!COLLISION_Read());
            break;
        }
    }
}

/* [] END OF FILE */
