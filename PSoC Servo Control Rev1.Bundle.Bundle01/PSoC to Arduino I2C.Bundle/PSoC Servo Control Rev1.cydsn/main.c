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
    while(1){
        CyGlobalIntEnable; /* Enable global interrupts. */
        uint16_t lowLimit = 300;
        uint16_t highLimit = 400;
        PCA9685_Custom_Begin();
        for(uint8_t servo = 0; servo<=5;servo++){
            PCA9685_Custom_setPWM(servo,0,lowLimit);   
        }
        while(true){
            for (uint8_t servo=0;servo<=5;servo++){
                for(uint16_t i =lowLimit ; i<highLimit;i++){
                    PCA9685_Custom_setPWM(servo,0,i);
                CyDelay(20);
                }
                for(uint16_t i =highLimit ; i>lowLimit;i--){
                    PCA9685_Custom_setPWM(servo,0,i);
                CyDelay(20);
                }
            }
            //PCA9685_Custom_Begin();
            //CyDelay(100);
        }
    }
}
/* [] END OF FILE */
