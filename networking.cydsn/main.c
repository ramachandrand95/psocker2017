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
//Address constants
#define ADDR1_Start 16
#define ADDR2_Start 25
#define ADDR3_Start 28
#define ADDR_length 2
#define BROADCAST 0
#define PROTOCOL_VERSION 0x01

//CRC constants
#define CRC_USE 128 //crcs not used
#define HEADER_CRC 0b1110111 

//period and counter for timer
#define COLL_PERIOD     52
#define COLL_COUNTER    51
#define IDLE_PERIOD     830
#define IDLE_COUNTER    829
//Receive timer stuff
#define RX_PERIOD   52
#define RX_COUNTER  51
//transmit timer stuff
#define TX_PERIOD     47 //gives 0.50ms or 500us for unipolar-rz at 1000bps
#define TX_COUNTER    46 //empirically tuned...
//serial buffer size
#define SERIAL_BUFFER_SIZE 500
//serial buffer
unsigned char SERIAL_BUFFER[SERIAL_BUFFER_SIZE];
unsigned char SERIAL_RX_BUFFER[SERIAL_BUFFER_SIZE];
int SERIAL_POS = 0;
int SERIAL_RX_POS = 0;
int UART_RX_DATA_READ_OUT = 0;
//flag to determine if the UART is connected
int uartConnected = 0;
//data cache for later use
unsigned char CONVERTED_DATA[SERIAL_BUFFER_SIZE][16];
int dataConvertedReadOutCount = 0;
char currentChar;
int dataSize;
int TX_Bit_Counter = 0; //keeps track of what would be a for loop in the ISR
int count = 0; //keeps track of which bit we're on
unsigned char RX_DATA[16]; //receieved data buffer
int RX_Bit_Counter = 0;
char RX_Char;
int RX_Lock = 0;
int bitConCatCount = 0;
unsigned char TX_Addr = 0; //transmit dest address
unsigned char TX_length = 0; //transmit length

CY_ISR(TIMER_RX_ISR){
    char characterRX = 0;
    
    TIMER_RX_STATUS; //clear stat
    //only receive data in c
    if(systemState != collisionState){
        TIMER_RX_Start();
        RX_DATA[RX_Bit_Counter] = Rx_Read(); //read bit
        ++RX_Bit_Counter;
        
    }else{
        //reset buffers when in collision 
        RX_Bit_Counter = 0;   
        SERIAL_RX_POS = 0;
        UART_RX_DATA_READ_OUT = 0;
        TIMER_RX_Stop();
        RX_Lock = 0;
    }
    //reset bit counter if we intook all the bits
    if(RX_Bit_Counter >= 15 ){
        RX_Bit_Counter = 0;
        TIMER_RX_Stop();
        RX_Lock = 0;
        TP_RX_SMPL_Write(0); //turn off test point, so we can measure time 
        
        for(int x = 15; x >= 0; x--){
            if(x == 15){
             characterRX = 0x00; //account for start bit   
            }
            if(x % 2 != 0){
                characterRX = (characterRX | (RX_DATA[x] << (bitConCatCount-1)));
                //UART_PutChar((RX_DATA[x])+0x30);
                ++bitConCatCount;
            }
        }
        SERIAL_RX_BUFFER[SERIAL_RX_POS] = characterRX;
        ++SERIAL_RX_POS;
       
    }
}

CY_ISR(Timer_TX_ISR_HANDLER)
{
	Timer_TX_STATUS; //clear TX timer
	//get data
	currentChar = SERIAL_BUFFER[SERIAL_POS];

	if((SERIAL_POS < dataSize) && systemState == idleState){ 
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
        CyDelayUs(495);
        ++TX_Bit_Counter;
        if(TX_Bit_Counter >= 16){
		    ++SERIAL_POS;
		    count = 0;
		    TX_Bit_Counter = 0;
            TX_Write(0);
        }
 
    }else if(systemState == collisionState){
    
       
    
    }
	

}

CY_ISR(BACKOFF){
    BACKOFF_STATUS;
    BACKOFF_Stop();
    systemState = idleState;
}

CY_ISR(TIMER)
{
   	Timer_1_STATUS; //clear timer
    
    if (!(lowFlag) ){
        systemState = idleState;
    } else {
        systemState = collisionState;
        TX_Write(0);
        TX_Bit_Counter = 0;    
        count = 0;
        int backoff = 0;
	    //reset current byte transmission 
	    //generate sudo-random backoff, normally distributed between backoff/128 seconds, where N is an int between 0 and 128
	    backoff = (PRS_Read()+1);
	    //CyDelay((double)(backoff/128.0)*1000); //use cydelay for now, which takes millis
        BACKOFF_WritePeriod((backoff/128.0)*1000);
        BACKOFF_WriteCounter(((backoff/128.0)*1000)-1);
        BACKOFF_Start();
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
    if(RX_Lock == 0){
        TIMER_RX_Start();
        RX_Lock = 1;
        TP_RX_SMPL_Write(1); //needed for test point sampling
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
    int printPrompt = 0;
    char input_buffer[SERIAL_BUFFER_SIZE];
    CyGlobalIntEnable;
    TimerISR_StartEx(TIMER);
    INT_RISING_StartEx(RISING);
    INT_FALLING_StartEx(FALLING);
    
    Timer_TX_Start();
    Timer_TX_WritePeriod(TX_PERIOD);
    Timer_TX_WriteCounter(TX_COUNTER);
    Timer_TX_ISR_StartEx(Timer_TX_ISR_HANDLER);
    
    TIMER_RX_WriteCounter(RX_COUNTER);
    TIMER_RX_WritePeriod(RX_PERIOD);
    TIMER_RX_ISR_StartEx(TIMER_RX_ISR);
    
    BACKOFF_ISR_StartEx(BACKOFF);
    PRS_Start();
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
        
        //get address
        if(printPrompt == 0 && uartConnected){
            int count = 0;
            TX_Addr = 0;
            printPrompt = 1;
            char input = 0;
            while(!UART_CDCIsReady());
            UART_PutString("Enter Address (3 digits): ");
            while(count < 3){
                while(UART_DataIsReady() == 0); //wait for digits
                //why minus 0x30? because these are ASCII chars from the keyboard...
                input = UART_GetChar();
                if(count == 0){
                    TX_Addr  += 100*(input - (0x30));
                    UART_PutChar(input);
                }else if(count == 1){
                    TX_Addr  += 10*(input - (0x30));
                    UART_PutChar(input);
                }else if (count == 2){
                    TX_Addr  += input - (0x30);   
                    UART_PutChar(input);
                }
                ++count;
            } 
            //Display print newline and prompt for message
            while(!UART_CDCIsReady());
            UART_PutCRLF();
            while(!UART_CDCIsReady());
            UART_PutString("Enter message: ");
            count = 6; //reset counter, accounting for header
            input = 0; //reset input
            //encode header
            
            SERIAL_BUFFER[0] = 0x00; //does not take into account starting bit
            SERIAL_BUFFER[1] = PROTOCOL_VERSION;
            SERIAL_BUFFER[2] = ADDR1_Start;
            SERIAL_BUFFER[3] = TX_Addr;
            SERIAL_BUFFER[4] = 0x00; //padding for now, will be replaced with actual length after user input
            SERIAL_BUFFER[5] = CRC_USE;
            SERIAL_BUFFER[6] = HEADER_CRC;
            
            //OD is the 'enter' key
            while(input != 0x0D){
                while(UART_DataIsReady() == 0); //wait for message data
                input = UART_GetChar();
                if(input != 0x0D){
                    SERIAL_BUFFER[count] = input;
                    while(!UART_CDCIsReady());
                    UART_PutChar(SERIAL_BUFFER[count]);
                    ++count;
                }
            }
            SERIAL_BUFFER[4] = count; //replace padding with actual message length
        }
        while(!UART_CDCIsReady());
        UART_PutCRLF();       
        
        //send data by setting variable
        SERIAL_POS = 0;
        printPrompt = 0;
        /*
        //check if the UART has data, then place in buffer
        if(UART_DataIsReady() != 0){
            dataSize = UART_GetAll(SERIAL_BUFFER);
            while(!UART_CDCIsReady());
            UART_PutCRLF();
            dataConvertedReadOutCount = 0;            
            SERIAL_POS = 0;
            printPrompt = 0;
        }
        */
        //write converted data to UART
    /*
        if(UART_CDCIsReady() != 0){
            if(dataConvertedReadOutCount < dataSize && SERIAL_POS == dataSize){
                for(int y = 0; y < 16; y++){
                 while(!UART_CDCIsReady());
                 //UART_PutChar(CONVERTED_DATA[dataConvertedReadOutCount][y]); 
                UART_PutChar(RX_DATA[y]);
                }
                ++dataConvertedReadOutCount;
                while(!UART_CDCIsReady());
                UART_PutCRLF();
            }
        }
    */
        
        if(UART_CDCIsReady() != 0){
            
            if(UART_RX_DATA_READ_OUT != SERIAL_RX_POS){
                for(int y = 0; y < SERIAL_RX_POS; y++){
                    int startHeaderReceieved = 0;
                    int verNumMatch = 0;
                    char sourceAddr = 0x00;
                    char destAddr = 0x00;
                    int dataLength = 0;
                    char CRCused = 0x00;
                    char HeaderCRC = 0x00;
                    int addrDataPrinted = 0;
                    int dataPrintedOut = 0;
                                        
                    while(!UART_CDCIsReady());
                    //check for start bit
                    if(y == 0){
                        if(SERIAL_RX_BUFFER[y] == 0x00){
                            startHeaderReceieved = 1;
                        }
                    }
                    //check for version number
                    else if(y == 1){
                        if(SERIAL_RX_BUFFER[y] == 0x01){
                            verNumMatch = 1;
                        }
                    }
                    //get source address
                    else if(y == 2){
                        sourceAddr = SERIAL_RX_BUFFER[y];
                    }
                    //get destination address
                    else if(y == 3){
                        destAddr = SERIAL_RX_BUFFER[y];
                    //get datalegnth     
                    }else if(y == 4){
                        dataLength = SERIAL_RX_BUFFER[y];
                    //get CRC related data
                    }else if(y == 5){
                        CRCused = SERIAL_RX_BUFFER[y];
                    } else if(y == 6){
                        HeaderCRC = SERIAL_RX_BUFFER[y];   
                    }
                    
                    //check version numbers and start bit
                    else if((startHeaderReceieved)&&(verNumMatch)){
                        //check that the destination address is this terminal 
                        if(destAddr == BROADCAST || 
                            ((destAddr >= ADDR1_Start) && (destAddr <= ADDR1_Start+ADDR_length)) ||
                            ((destAddr >= ADDR2_Start) && (destAddr <= ADDR2_Start+ADDR_length)) ||
                            ((destAddr >= ADDR3_Start) && (destAddr <= ADDR3_Start+ADDR_length))){
                            
                            if(addrDataPrinted == 0){
                                addrDataPrinted = 1; 
                                while(!UART_CDCIsReady());
                                UART_PutString("Source Address: ");
                                while(!UART_CDCIsReady());
                                UART_PutChar(sourceAddr);
                                while(!UART_CDCIsReady());
                                UART_PutCRLF();
                                while(!UART_CDCIsReady());
                                UART_PutString("Destination Address: ");
                                while(!UART_CDCIsReady());
                                UART_PutChar(destAddr);
                                while(!UART_CDCIsReady());
                                UART_PutCRLF();
                            }
                            //print out data
                            if(dataPrintedOut < dataLength){
                                while(!UART_CDCIsReady());
                                UART_PutChar(SERIAL_RX_BUFFER[y]);
                                ++dataPrintedOut;
                            }else{
                            //we are out of data here
                            while(!UART_CDCIsReady());
                            UART_PutCRLF();
                            }
                                
                        }
                    }
                    UART_PutChar(SERIAL_RX_BUFFER[y]); //send data to UART
                    ++UART_RX_DATA_READ_OUT;
                    //while(!UART_CDCIsReady());
                    //UART_PutCRLF();
                }
            }
                SERIAL_RX_POS = 0;
                UART_RX_DATA_READ_OUT = 0;
                        
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
