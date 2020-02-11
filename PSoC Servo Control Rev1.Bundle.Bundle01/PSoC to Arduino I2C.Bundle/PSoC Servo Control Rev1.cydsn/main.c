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
#include "PCA9685_Custom.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    PCA9685_Custom_Begin();
    for(;;){

        uint16_t lowLimit = 0;
        uint16_t highLimit = 600;
        
        for(uint16_t i =lowLimit ; i<highLimit;i++){
        PCA9685_Custom_setPWM(1,0,i);
        PCA9685_Custom_setPWM(5,0,i);
        CyDelay(10);
        }
        for(uint16_t i =highLimit ; i>lowLimit;i--){
        PCA9685_Custom_setPWM(1,0,i);
        PCA9685_Custom_setPWM(5,0,i);
        CyDelay(10);
        }
    }
}

/* [] END OF FILE */
