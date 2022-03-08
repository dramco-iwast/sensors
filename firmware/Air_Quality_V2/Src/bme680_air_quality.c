/*
 * bme680_air_quality.c
 *
 *  Created on: 30 Nov 2020
 *      Author: sarah
 */

#include "stdio.h"
#include "stdlib.h"
#include "bme680_air_quality.h"
#include "gpio.h"
#include "usart.h"
#include "main.h"

#ifdef SENSOR_TYPE
  #if (SENSOR_TYPE == BME680)
    //#warning "Compiling for BME680"
  #endif
#endif

extern uint8_t measurementData[D_LEN];
extern uint16_t temp16;
extern uint16_t pres16;
extern uint16_t humi16;
extern uint16_t iaq16;
//extern intGenerated;
extern generateIntReq;
//extern timeOfInt;
extern MasterReset;

// threshold settings for each metric
// temperature
 uint8_t tempTreshEnabled = 0;
 uint16_t tempTLH = 0;
 uint16_t tempTLL = 0;
 bool tempTLHExceeded = false;
 bool tempTLLExceeded = false;
// atm. pressure
 uint8_t presTreshEnabled = 0;
 uint16_t presTLH = 0;
 uint16_t presTLL = 0;
 bool presTLHExceeded = false;
 bool presTLLExceeded = false;
// air quality index
 uint8_t iaqTreshEnabled = 0;
 uint16_t iaqTLH = 0;
 uint16_t iaqTLL = 0;
 bool iaqTLHExceeded = false;
 bool iaqTLLExceeded = false;
// humidity
 uint8_t humiTreshEnabled = 0;
 uint16_t humiTLH = 0;
 uint16_t humiTLL = 0;
 bool humiTLHExceeded = false;
 bool humiTLLExceeded = false;

uint8_t rslt;
//BME680_t gas_sensor;

bool init = true;
bool polledMeasurement = false;
bool measurementRunning = false;

uint32_t maxDataGasResistance = 0x0001D4C0;
uint32_t dataGasResistanceVar = 0x0000023F;

void generateInt(void);
void measure(void);


void BME680_Init(void)
{

}

void BME680_Measure(void)
{
//  char uart_buf[100];
//  int uart_buf_len;
//  uart_buf_len = sprintf(uart_buf, "BME680_Measure(): Motherboard requested measurement.\r\n");
//  HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
  polledMeasurement = true;
  measure();
}

void BME680_Loop(void)
{

}

void BME680_GetData(uint8_t * data, uint8_t  * length)
{
  uint8_t i;
  for(i=0; i<D_LEN; i++) data[i] = measurementData[i];
  *length = D_LEN;
}

void BME680_SetThreshold(uint8_t metric, uint8_t * thresholdData)
{
  char uart_buf[200];
  int uart_buf_len;
//    uart_buf_len = sprintf(uart_buf, "Setting thresholds for metric 0x%2X.\r\n",metric);
//    HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
  switch(metric)
  {
    case METRIC_TEMPERATURE:
    {
      tempTreshEnabled = thresholdData[1];
      tempTLL = (uint16_t)((thresholdData[2]<<8) | thresholdData[3]);
      tempTLH = (uint16_t)((thresholdData[4]<<8) | thresholdData[5]);
      //uart_buf_len = sprintf(uart_buf, "Thresholds set for temperature: tempTLL = 0x%4X, tempTLH = 0x%4X. Time = %dms.\r\n",tempTLL,tempTLH,(int)(get_timestamp_us()/1000));
      //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
    } break;
    case METRIC_PRESSURE:
    {
      presTreshEnabled = thresholdData[1];
      presTLL = (uint16_t)((thresholdData[2]<<8) | thresholdData[3]);
      presTLH = (uint16_t)((thresholdData[4]<<8) | thresholdData[5]);
      //uart_buf_len = sprintf(uart_buf, "Thresholds set for pressure: presTLL = 0x%4X, presTLH = 0x%4X.\r\n",presTLL,presTLH);
      //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
    } break;
    case METRIC_IAQ:
    {
      iaqTreshEnabled = thresholdData[1];
      iaqTLL = (uint16_t)((thresholdData[2]<<8) | thresholdData[3]);
      iaqTLH = (uint16_t)((thresholdData[4]<<8) | thresholdData[5]);
      //uart_buf_len = sprintf(uart_buf, "Thresholds set for IAQ: iaqTLL = 0x%4X, iaqTLH = 0x%4X.\r\n",iaqTLL,iaqTLH);
      //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
    } break;
    case METRIC_HUMIDITY:
    {
      humiTreshEnabled = thresholdData[1];
      humiTLL = (uint16_t)((thresholdData[2]<<8) | thresholdData[3]);
      humiTLH = (uint16_t)((thresholdData[4]<<8) | thresholdData[5]);
      //uart_buf_len = sprintf(uart_buf, "Thresholds set for humidity: humiTLL = 0x%4X, humiTLH = 0x%4X. Time = %dms.\r\n",humiTLL,humiTLH,(int)(get_timestamp_us()/1000));
      //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
      MasterReset = 1;
    } break;
    default: break;
  }
}

void generateInt(void)
{

//  intGenerated = 1;
//  char uart_buf[200];
//  int uart_buf_len;
  //        sleep(150); // 150ms delay --> SLEEP WERKT NIET!!!
//  int t_ms = 500000;
//  while(t_ms > 0)
//  {
//    t_ms--;
//  }
  HAL_GPIO_WritePin(INT_GPIO_Port, INT_Pin, GPIO_PIN_RESET);
//  sleep(1); // 1ms delay --> SLEEP WERKT NIET!!! (ook HAL_Delay werkt niet...)
//  t_ms = 5000;
//  while(t_ms > 1)
//  {
//    t_ms--;
//  }
  HAL_Delay(1);
  HAL_GPIO_WritePin(INT_GPIO_Port, INT_Pin, GPIO_PIN_SET);
//  uart_buf_len = sprintf(uart_buf, "generateINT(): INT generated.\r\n");
//  HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
}

void measure(void)
{
  char uart_buf[200];
  int uart_buf_len;
  if(polledMeasurement) // motherboard has requested a measurement
  {
	polledMeasurement = false;
    uart_buf_len = sprintf(uart_buf, "Generate INT for requested measurement.\r\n");
//    uart_buf_len = sprintf(uart_buf, "Generate INT for requested measurement. Time = %dms.\r\n",(int)(get_timestamp_us()/1000));
    HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
    // notify the motherboard that the requested measurement has completed
//    sleep(150); // 150ms delay
      generateInt();
  }
  else // automatic measurement -> check thresholds
  {
    bool thresholdExceeded = false;
    // check temperature thresholds
//    uart_buf_len = sprintf(uart_buf, "Generate INT because threshold is exceeded.\r\n");
    uart_buf_len = sprintf(uart_buf, "Generate INT because threshold is exceeded. Time = %dms.\r\n",(int)(get_timestamp_us()/1000));
    HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
    if(tempTreshEnabled)
    {
      if(temp16 < tempTLL)
      {
        if(!tempTLLExceeded)
        {
          thresholdExceeded = true;
          tempTLLExceeded = true;
        }
      }
      else
      {
        tempTLLExceeded = false;
      }
      if(temp16 > tempTLH)
      {
        if(!tempTLHExceeded)
        {
          thresholdExceeded = true;
          tempTLHExceeded = true;
        }
      }
      else
      {
        tempTLHExceeded = false;
      }
    }
    // check pressure thresholds
    if(presTreshEnabled)
    {
      if(pres16 < presTLL)
      {
        if(!presTLLExceeded)
        {
          thresholdExceeded = true;
          presTLLExceeded = true;
        }
      }
      else
      {
        presTLLExceeded = false;
      }
      if(pres16 > presTLH)
      {
        if(!presTLHExceeded)
        {
          thresholdExceeded = true;
          presTLHExceeded = true;
        }
      }
      else
      {
        presTLHExceeded = false;
      }
    }
    // check iaq thresholds
    if(iaqTreshEnabled)
    {
      if(iaq16 < iaqTLL)
      {
        if(!iaqTLLExceeded)
        {
          thresholdExceeded = true;
          iaqTLLExceeded = true;
        }
      }
      else
      {
        iaqTLLExceeded = false;
      }
      if(iaq16 > iaqTLH)
      {
        if(!iaqTLHExceeded)
        {
          thresholdExceeded = true;
          iaqTLHExceeded = true;
        }
      }
      else
      {
        iaqTLHExceeded = false;
      }
    }
    // check humidity thresholds
    if(humiTreshEnabled)
    {
      if(humi16 < humiTLL)
      {
        if(!humiTLLExceeded)
        {
          thresholdExceeded = true;
          humiTLLExceeded = true;
        }
      }
      else
      {
        humiTLLExceeded = false;
      }
      if(humi16 > humiTLH)
      {
        if(!humiTLHExceeded)
        {
          thresholdExceeded = true;
          humiTLHExceeded = true;
        }
      }
      else
      {
        humiTLHExceeded = false;
      }
    }
    if(thresholdExceeded)
    {
   	  generateInt();
      generateIntReq = 1;
    }
  }
}
