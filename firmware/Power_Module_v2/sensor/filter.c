/*
 * Based on: https://github.com/sebnil/Moving-Avarage-Filter--Arduino-Library-
*/
#include "filter.h"

filter_t filter;
volatile filter_highest_t f;

filter_init(unsigned int newDataPointsCount)
{
  filter.k = 0; //initialize so that we start to write at index 0
  if (newDataPointsCount < MAX_DATA_POINTS)
    filter.dataPointsCount = newDataPointsCount;
  else
    filter.dataPointsCount = MAX_DATA_POINTS;

  for (filter.i = 0; filter.i < filter.dataPointsCount; filter.i++)
  {
    filter.values[filter.i] = 0; // fill the array with 0's
  }
}

float filter_process(float in)
{
  filter.out = 0;

  filter.values[filter.k] = in;
  filter.k = (filter.k + 1) % filter.dataPointsCount;

  for (filter.i = 0; filter.i < filter.dataPointsCount; filter.i++)
  {
    filter.out += filter.values[filter.i];
  }

  return filter.out / filter.dataPointsCount;
}

filter_highest_init(unsigned int newDataPointsCount)
{
    // Initialize filter to all zeros
    for(uint8_t i=0; i<FILTER_HIGHEST_LEN; i++)
    {
        f.values[i] = 0.0;
    }
    f.i = 0;
}

float filter_highest(float in)
{
    // Store value in filter
    f.values[f.i] = in;
    
    // Edge conditions
    // Increment filter value
    f.i++;
    // If end of loop is reached -> set place counter to zero
    if(f.i >= FILTER_HIGHEST_LEN) f.i=0;
    
    // Calculate highest value in array
    float temp = 0;
    for(uint8_t i=0; i<FILTER_HIGHEST_LEN; i++)
    {
        if(f.values[i] > temp) temp=f.values[i];
    }

    return temp;
}
