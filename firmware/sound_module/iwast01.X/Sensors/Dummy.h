/* 
 * File:   dummy.h
 * Author: geoffrey
 *
 * Created on 11 september 2019, 13:26
 */

#ifndef DUMMY_H
#define	DUMMY_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>


#define TYPE_BYTE   0x21
#define LENGTH_BYTE 0x02

#define SLAVE_ADDRESS 0x65


#define samples 400 // amount of samples

extern uint8_t measurementData[LENGTH_BYTE] = {0x00, 0x00};     // Data that will be send via I2C whenever the threshold value is exceeded
bool reset = false;                                             // when true, the value of "value"
uint16_t x = 0;         
uint16_t maxValue = 0;



void doMeasurement(void);
void prepTransmission(uint16_t);
void getValue(void);
void initializeADC(void);
void stopADC(void);
void generateInt(void);
void setThreshold(uint16_t);
void translateData(uint8_t enable,uint8_t MSBLT,uint8_t LSBLT,uint8_t MSBUP,uint8_t LSBUT);
void enableMic(void);
void disableMic(void);
void toggleInt(void);


#endif	/* DUMMY_H */

