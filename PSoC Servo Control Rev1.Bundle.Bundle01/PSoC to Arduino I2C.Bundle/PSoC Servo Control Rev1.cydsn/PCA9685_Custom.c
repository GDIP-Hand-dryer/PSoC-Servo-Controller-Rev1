/*!
 *  @file Adafruit_PWMServoDriver.cpp
 *
 *  @mainpage Adafruit 16-channel PWM & Servo driver
 *
 *  @section intro_sec Introduction
 *
 *  This is a library for the 16-channel PWM & Servo driver.
 *
 *  Designed specifically to work with the Adafruit PWM & Servo driver.
 *
 *  Pick one up today in the adafruit shop!
 *  ------> https://www.adafruit.com/product/815
 *
 *  These displays use I2C to communicate, 2 pins are required to interface.
 *
 *  Adafruit invests time and resources providing this open source code,
 *  please support Adafruit andopen-source hardware by purchasing products
 *  from Adafruit!
 *
 *  @section author Author
 *
 *  Limor Fried/Ladyada (Adafruit Industries).
 *
 *  @section license License
 *
 *  BSD license, all text above must be included in any redistribution
 */
#include <PCA9685_Custom.h>
#include <math.h>
#define I2C_SLAVE_ADDR      (0x40u)

//float freq = 1600.0;
float oscillator_frequency = 27000000;

//Set servo maximum limits here
uint16_t Servo_Limit_Low[6]={90,90,90,90,90,90};
uint16_t Servo_Limit_High[6]={560,560,560,560,560,560};

void PCA9685_Custom_Begin(){
    I2C_1_Start();
    PCA9685_Custom_Reset();
    PCA9685_Custom_setPWMFreq(60);
}

void PCA9685_Custom_Reset(void) {
 PCA9685_Custom_Write8(PCA9685_MODE1, 0x80);
}

void PCA9685_Custom_setPWM(uint8 num, uint16 on, uint16 off){
    
    //limit servo movement to between low and high limits
    if(off<Servo_Limit_Low[num]){
        off=Servo_Limit_Low[num];
    }
    else if(off>Servo_Limit_High[num]){
        off=Servo_Limit_High[num];
    }
    else{
    }
       
    I2C_1_MasterSendStart(I2C_SLAVE_ADDR, I2C_WRITE_XFER_MODE);
    I2C_1_MasterWriteByte(CH0_ON_L+(0x04*num));
    I2C_1_MasterWriteByte(on);
    I2C_1_MasterWriteByte(on>>8);
    I2C_1_MasterWriteByte(off);
    I2C_1_MasterWriteByte(off>>8);
    I2C_1_MasterSendStop();
}

void PCA9685_Custom_setPWMFreq(float freq) {
  //Serial.print("Attempting to set freq ");
  //Serial.println(freq);
  freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
  float prescaleval = 25000000;
  prescaleval /= 4096;
  prescaleval /= freq;
  prescaleval -= 1;
 
  uint8_t prescale = floor(prescaleval + 0.5);
   
  uint8_t oldmode = PCA9685_Custom_Read8(PCA9685_MODE1);
  uint8_t newmode = (oldmode&0x7F) | 0x10; // sleep
  PCA9685_Custom_Write8(PCA9685_MODE1, newmode); // go to sleep
  PCA9685_Custom_Write8(PCA9685_PRESCALE, prescale); // set the prescaler
  PCA9685_Custom_Write8(PCA9685_MODE1, oldmode);
  CyDelayUs(5);  
  PCA9685_Custom_Write8(PCA9685_MODE1, oldmode | 0xa1);  //  This sets the MODE1 register to turn on auto increment.
}

uint8_t PCA9685_Custom_Write8(uint8_t reg, uint8_t data){
    uint8_t Result;
    if((Result = I2C_1_MasterSendStart(I2C_SLAVE_ADDR, I2C_WRITE_XFER_MODE))) return Result;
    if((Result = I2C_1_MasterWriteByte(reg))) return Result;
    if((Result = I2C_1_MasterWriteByte(data))) return Result;
    if((Result = I2C_1_MasterSendStop())) return Result;
    return Result;
}

uint8_t PCA9685_Custom_Read8(uint8_t reg){
  uint8_t response = 0x00;
  I2C_1_MasterSendStart(I2C_SLAVE_ADDR, I2C_WRITE_XFER_MODE);
  I2C_1_MasterWriteByte(reg);
  I2C_1_MasterSendRestart(I2C_SLAVE_ADDR, I2C_READ_XFER_MODE);
  response =  I2C_1_MasterReadByte(I2C_NAK_DATA);
  I2C_1_MasterSendStop();

  return response; 
}
/* [] END OF FILE */
