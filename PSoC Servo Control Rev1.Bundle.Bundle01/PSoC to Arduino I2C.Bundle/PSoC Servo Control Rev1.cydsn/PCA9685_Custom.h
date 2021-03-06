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

#ifndef PCA9685_Custom_H
#define PCA9685_Custom_H

#include <project.h>
#include <stdio.h>
#include <stdbool.h>
    
    
#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define CH0_ON_L 0x6
#define CH0_ON_H 0x7
#define CH0_OFF_L 0x8
#define CH0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD
    
    
#define I2C_READ_XFER_MODE             (0x01u)    /* Read */
#define I2C_WRITE_XFER_MODE            (0x00u)    /* Write */
#define I2C_ACK_DATA                   (0x01u)    /* Send ACK */
#define I2C_NAK_DATA                   (0x00u)    /* Send NAK */

//void PCA9685_Custom_ServoDriver(); // default 0x40
void PCA9685_Custom_Begin(void);
void PCA9685_Custom_Reset(void);
void PCA9685_Custom_setPWM(uint8 num, uint16 on, uint16 off);
void PCA9685_Custom_setPWMFreq(float freq);
uint8_t PCA9685_Custom_Write8(uint8_t reg,uint8_t data);
uint8_t PCA9685_Custom_Read8(uint8_t reg);
/* [] END OF FILE */
#endif