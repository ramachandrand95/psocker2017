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

#define COLL_PERIOD     52
#define COLL_COUNTER    51
#define IDLE_PERIOD     830
#define IDLE_COUNTER    829

CY_ISR(TIMER)
{
   	Timer_1_STATUS;
    
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

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    while(1){
        switch(systemState){
            case idleState :;
                IDLE_Write(1);
                BUSY_Write(!IDLE_Read());
                COLLISION_Write(!IDLE_Read());
            break;
            
            case busyState:
                BUSY_Write(1);
                IDLE_Write(!BUSY_Read());
                COLLISION_Write(!BUSY_Read());
            break;
            
            case collisionState:;
                COLLISION_Write(1);
                IDLE_Write(!COLLISION_Read());
                BUSY_Write(!COLLISION_Read());
            break;
        }
    }
}

/* [] END OF FILE */
