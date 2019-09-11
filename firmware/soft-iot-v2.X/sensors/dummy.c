#include "dummy.h"

uint8_t measurementData[LENGTH_BYTE] = {0x00, 0x00, 0x00, 0x00};

void doMeasurement(void){
    measurementData[0] += 1;
    measurementData[1] += 2;
    measurementData[2] += 4;
    measurementData[3] += 8;
}