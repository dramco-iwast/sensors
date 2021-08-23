#ifndef MovingAverageFilter_h
#define MovingAverageFilter_h

#include <math.h>
#include "string.h"
#include "stdint.h"

#define FILTER_NUM_AVG  5
#define FILTER_HIGHEST_LEN  5

#define MAX_DATA_POINTS 20

filter_init(unsigned int newDataPointsCount);
float filter_process(float in);

filter_highest_init(unsigned int newDataPointsCount);
float filter_highest(float in);

typedef struct{
    float values[MAX_DATA_POINTS];
    int k; // k stores the index of the current array read to create a circular memory through the array
    int dataPointsCount;
    float out;
    int i; // just a loop counter
}filter_t;

typedef struct{
    float values[FILTER_HIGHEST_LEN]; // store measurements
    uint8_t i; // just a loop counter
}filter_highest_t;

#endif
