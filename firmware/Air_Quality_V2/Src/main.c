/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stdio.h"
#include "stdlib.h"
#include "global.h"
#include "bsec_integration.h"
#include "bsec_datatypes.h"
#include "bsec_serialized_configurations_iaq.h"
#include "debugPrint.h"
// include sensor
#ifdef SENSOR_TYPE
    #if (SENSOR_TYPE == BUTTONS)
        #include "Sensors/buttons.h"
    #elif (SENSOR_TYPE == SOUND_LEVEL)
        #include "Sensors/sound_level.h"
    #elif (SENSOR_TYPE == BME680)
        #include "bme680_air_quality.h"
    #else
        #warning "Make sure your build settings in global.h are correct."
        #error "Unsupported sensor type."
    #endif
#else
    #warning "Make sure your build settings in global.h are correct."
    #error "Sensor type is undefined."
#endif

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

Device_API_t sensorAPI = SENSOR_API;

#ifndef TYPE_BYTE
    #error "TYPE_BYTE is not defined"
#elif (~(~TYPE_BYTE + 0) == 0 && ~(~TYPE_BYTE + 1) == 1)
    #error "TYPE_BYTE is defined, but has no value"
#endif

#ifndef M_NR
    #error "M_NR is not defined"
#elif (~(~M_NR + 0) == 0 && ~(~M_NR + 1) == 1)
    #error "M_NR is defined, but has no value"
#endif

#ifndef SLAVE_ADDRESS
    #error "SLAVE_ADDRESS is not defined"
#elif (~(~SLAVE_ADDRESS + 0) == 0 && ~(~SLAVE_ADDRESS + 1) == 1)
    #error "SLAVE_ADDRESS is defined, but has no value"
#endif

uint8_t mData[2 * M_NR];
uint8_t mDataLength;
uint8_t Ready;
uint8_t MasterReset = 0;

uint8_t measurementData[D_LEN] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t measurementDataForI2C[D_LEN] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t temp16 = 0x0000;
uint16_t pres16 = 0x0000;
uint16_t humi16 = 0x0000;
uint16_t iaq16  = 0x0000;
uint8_t iaqacc = 0x00;
uint8_t intGenerated = 0;
uint8_t generateIntReq = 0; // if CMD_START_MEASUREMENT: generateIntReq = 1. The interrupt will be given AFTER a measurement (ULP or ULP PLUS) has been done.
uint8_t firstCmdStartMeasurement = 0; // to know when master requests for a measurement the first time
uint8_t mMeasurementReq = 0;
uint8_t mDataReq = 0;
uint8_t mDataSend = 0;
uint8_t mSetThresholds = 0;
uint8_t SetThresholds = 0;
uint8_t startBME680 = 0;
uint8_t DelayULPPStart = 0;


int64_t currentTime;
int64_t previousTime1;
int64_t previousTime2;

uint32_t n_samples = 0;
int32_t save_intvl = 100;

int64_t timeOfCmdStartMeasurement;
int64_t realTimeOfCmdStartMeasurement;
int64_t timeOfCmdIntToggleByMaster;
int64_t timeOfSetThresholds;

int64_t timeOfMeasurementDataPrint;
int64_t timeEllapsedSinceLastMeasurement;
int64_t timeULPStart;
int64_t timeDelayULPPStart;
int64_t timeDiffULPStart;
int64_t timeOfMasterIntToggle;
int64_t timeOfMDataReq;

int64_t PrevioustimeOfCmdStartMeasurement;
//int64_t timeOfIntReq;
int64_t timeOfIntExecution;
uint8_t alignIntReqWithBsec = 0;
uint8_t intExecute = 0;

int64_t timeOfCmdGetMData;
int64_t timeOfCmdPoll;
int64_t cycleEndTime;
int64_t cycletimeBSEC;
int64_t startTimeOfSaveBsecStatus;
int64_t endTimeOfSaveBsecStatus;
int64_t slaveCycleTime = 300000;

int64_t bsecCycle = 3000000; // this is the cycle of bsec, not bme680! Expressed in microseconds, set to 3s.
int64_t firstCycle = 60000000; // this is when the first cycle of bsec needs to start AFTER POLL command from master, set to 1s.

// DATA EEPROM Flash address
uint32_t Address = 0;
uint8_t saveBsec = 0;
uint8_t saveBsecState = 0;
uint8_t syncSaveBsecState = 0;
uint16_t saveBsecStateAanpassing = 0;

uint8_t processLed = 10;
uint8_t startFirstMeasurement = 0;
uint8_t cmdStartMeasurement = 0;
uint8_t cmdPoll = 0;
uint8_t cmdDeviceType = 0;
uint8_t cmdGetMNr = 0;
uint8_t cmdIntToggleByMaster = 0;
uint8_t cmdGetMData = 0;
uint MasterCycleCounter = 0;

uint8_t intExecuteInNextWakeUp = 0;
int64_t timeOfIntExecutionInNextWakeUp = 0;
uint8_t generateIntReqInNextWakeUp = 0;
uint8_t alignIntReqWithBsecInNextWakeUp = 0;

/**
  * @brief Variables related to Slave process
  */
const char* aSlaveInfo[]      = {
                  "STM32L152RE",
                  "1.2.3"};

uint8_t       aSlaveReceiveBuffer[0xF]  = {0};
uint8_t*      pSlaveTransmitBuffer      = 0;
__IO uint8_t  ubSlaveNbDataToTransmit   = 0;
uint8_t       ubSlaveInfoIndex          = 0xFF;
__IO uint8_t  ubSlaveReceiveIndex       = 0;
uint32_t      uwTransferDirection       = 0;
__IO uint32_t uwTransferInitiated       = 0;
__IO uint32_t uwTransferEnded           = 0;
uint8_t       mySlaveTransmitBuffer     = 0xAA;
uint8_t       slaveTransferOngoing      = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//	char uart_buf[50];
	//	int uart_buf_len;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  //HAL_Delay(100);
  //setup_bsec_bme680_interface();
  //HAL_Delay(100);

  //  int64_t previousTime1;
  //  previousTime1 = get_timestamp_us();

   // previousTime2 = get_timestamp_us();
  //  int64_t currentTime;


    /* Start of bsec_iot_loop function before while (1) replacement */
    /* Timestamp variables */
    uint64_t time_stamp = 0;
    uint64_t time_stamp_interval_ms = 0;

    /* Allocate enough memory for up to BSEC_MAX_PHYSICAL_SENSOR physical inputs*/
    bsec_input_t bsec_inputs[BSEC_MAX_PHYSICAL_SENSOR];

    /* Number of inputs to BSEC */
    uint8_t num_bsec_inputs = 0;

    /* BSEC sensor settings struct */
    bsec_bme_settings_t sensor_settings;

    /* Save state variables */
    uint8_t bsec_state[BSEC_MAX_STATE_BLOB_SIZE];
    uint8_t work_buffer[BSEC_MAX_STATE_BLOB_SIZE];
    uint32_t bsec_state_len = 0;

    extern bsec_data bsec_value;

    bsec_value.timestamp = 0;
    bsec_value.iaq = 0.0f;
    bsec_value.iaq_accuracy = 0;
    bsec_value.temp = 0.0f;
    bsec_value.raw_temp = 0.0f;
    bsec_value.raw_pressure = 0.0f;
    bsec_value.humidity = 0.0f;
    bsec_value.raw_humidity = 0.0f;
    bsec_value.raw_gas = 0.0f;
    bsec_value.static_iaq = 0.0f;
    bsec_value.static_iaq_accuracy = 0;
    bsec_value.co2_equivalent = 0.0f;
    uint8_t co2_accuracy = 0;
    bsec_value.breath_voc_equivalent = 0.0f;
    uint8_t breath_voc_accuracy = 0;
    bsec_value.comp_gas_value = 0.0f;
    uint8_t comp_gas_accuracy = 0;
    bsec_value.gas_percentage = 0.0f;
    bsec_value.gas_percentage_acccuracy = 0;

    bsec_library_return_t bsec_status = BSEC_OK;
    /* End of bsec_iot_loop function before while (1) replacement */

    char uart_buf[200];
    int uart_buf_len;

    // I2C buffer for commands reception

    // Interrupt line to master HIGH
    HAL_GPIO_WritePin(INT_GPIO_Port, INT_Pin, GPIO_PIN_SET);
    Ready = 0; // INT_Pin high

    uint64_t time_next_measurement = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	/*##-2- Put I2C peripheral in Listen address match code process ##########*/
	/* This action will allow I2C periphal to able to treat Master request when
	 * necessary depending of transfer direction requested by Master */
	if ((currentTime - previousTime2) >= TICK) // do this every ms
	{
		if(HAL_I2C_EnableListen_IT(&hi2c1) != HAL_OK)
		{
		  /* Transfer error in reception process */
		  //Error_Handler();
		  //uart_buf_len = sprintf(uart_buf, "HAL_I2C_EnableListen_IT(&hi2c1) error (in while loop).\r\n");
		  //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
		}
		previousTime2 = currentTime;
	}


//	if ((currentTime - previousTime1) >= TICK) // do this every ms
//	{
//    ...
//	  previousTime1 = currentTime;
//	}
    currentTime = get_timestamp_us();

//	if (MasterReset) // reset at master occurred
//	{
//	  if (generateIntReq && (currentTime >= timeOfIntReq))
	  if (generateIntReq && (currentTime >=  (timeOfCmdStartMeasurement + 2500000)))
	  {
		generateIntReq = 0;
		alignIntReqWithBsec = 1;
	  }

	  if(generateIntReqInNextWakeUp && (currentTime >= (timeOfCmdStartMeasurement + 17000000)))
	  {
		generateIntReqInNextWakeUp = 0;
		alignIntReqWithBsecInNextWakeUp = 1;
	  }

	  if (intExecuteInNextWakeUp && (currentTime >= timeOfIntExecutionInNextWakeUp) && MasterCycleCounter > 1)
	  {
		intExecuteInNextWakeUp = 0;
	    if ((get_timestamp_us() - timeOfCmdStartMeasurement) < 21000000)
	    {
		  sensorAPI.Measure();
	    }
	    else
	    {
		  uart_buf_len = sprintf(uart_buf, "Also no INT generated in the second wake-up event to avoid possible RESET. Time elapsed since last measurement request = %dms. MasterCycleCounter = %d.\r\n",(int)((get_timestamp_us() - timeOfCmdStartMeasurement)/1000),(int)MasterCycleCounter);
		  HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
	    }
	  }

	  if (intExecute && (currentTime >= timeOfIntExecution) && MasterCycleCounter > 1)
      {
	    intExecute = 0;
	    // if time elapsed is > 8s since measurement request, then there is a risk that the radio will work during the next wake-up
	    // resulting in a watchdog reset of the master with a reset as a consequence.
	    // To avoid a possible reset, it is better NOT to give the INT if this occurs.
	    // It is also important to take this into account if a threshold is exceeded. See bme680_air_quality.c, where the INT request can also be set.
	    if ((get_timestamp_us() - timeOfCmdStartMeasurement) < 5500000)
	    {
		  sensorAPI.Measure();
	    }
	    else
	    {
		  uart_buf_len = sprintf(uart_buf, "No INT generated in this wake-up event to avoid possible RESET. Time elapsed since last measurement request = %dms. MasterCycleCounter = %d.\r\n",(int)((get_timestamp_us() - timeOfCmdStartMeasurement)/1000),(int)MasterCycleCounter);
		  HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
		  generateIntReqInNextWakeUp = 1;
		  //intExecuteInNextWakeUp = 1;
		  //timeOfIntExecuteInNextWakeUp = timeOfCmdStartMeasurement + 17000000;
		}
	  }


	  if ((((currentTime - previousTime1) >= bsecCycle) && (firstCmdStartMeasurement == 2))  || (firstCmdStartMeasurement == 1)) // do this every 3s
//	  if ((currentTime - previousTime1) >= bsecCycle) // do this every 3s
	  {
		if (firstCmdStartMeasurement == 1)
		{
		  firstCmdStartMeasurement = 2;
		  generateIntReq = 1;
		  //timeOfIntReq = get_timestamp_us();
		}
		if ((MasterCycleCounter++ >= 100) || (MasterCycleCounter == 1))
		{
		  uart_buf_len = sprintf(uart_buf, "Start measurement in ULP mode. Current time = %ds. Time elapsed since last ULP measurement = %dms. MasterCycleCounter = %d.\r\n",(int)(currentTime/1000000),(int)((currentTime-timeULPStart)/1000),(int)MasterCycleCounter);
	      HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
	      timeULPStart = get_timestamp_us();
	      MasterCycleCounter = 1;
		}
		/* get the timestamp in nanoseconds before calling bsec_sensor_control() */
		time_stamp = currentTime * 1000;
	    /* Retrieve sensor settings to be used in this time instant by calling bsec_sensor_control */
		bsec_status = bsec_sensor_control(time_stamp, &sensor_settings);
	    if (bsec_status != BSEC_OK)
	    {
	      uart_buf_len = sprintf(uart_buf, "bsec_sensor_control issue, bsec_status = %d. Time since last bsec control request = %dms\r\n",(int)bsec_status,(int)((currentTime - previousTime1)/1000));
	      HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
	    }
	    /* Trigger a measurement if necessary */
	    bme680_bsec_trigger_measurement(&sensor_settings, sleep);
	    /* Read data from last measurement */
	    num_bsec_inputs = 0;
	    bme680_bsec_read_data(time_stamp, bsec_inputs, &num_bsec_inputs, sensor_settings.process_data);
	    /* Time to invoke BSEC to perform the actual processing */
	    bme680_bsec_process_data(bsec_inputs, num_bsec_inputs, output_ready);
	    /* Retrieve and store state if save_intvl passed */
	    if (n_samples >= save_intvl)
	    {
	      bsec_status = bsec_get_state(0, bsec_state, sizeof(bsec_state), work_buffer, sizeof(work_buffer), &bsec_state_len);
	      if (bsec_status == BSEC_OK)
	      {
	        state_save(bsec_state, bsec_state_len);
	      }
	      n_samples = 0;
	    }
	    previousTime1 = currentTime;
		HAL_Delay(50);
		HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(50);
		HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	    cycletimeBSEC = (get_timestamp_us()-currentTime)/1000;
	    if (cycletimeBSEC > 110)
	    {
	      uart_buf_len = sprintf(uart_buf, "Duration BSEC cycle =  %dms, MasterCycleCounter = %d\r\n",(int)cycletimeBSEC,(int)MasterCycleCounter);
	      HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
	    }
//	    if (generateIntReq)
//	    {
//	      timeOfIntReq = get_timestamp_us() + 1000000; // +1s, to generate the INT between 2 bsec cycles
//	    }

	    if (alignIntReqWithBsec)
	    {
	      alignIntReqWithBsec = 0;
	      timeOfIntExecution = currentTime + 500000; // +0.5s, to generate the INT between 2 bsec cycles
	      intExecute = 1;
	    }
	    if(alignIntReqWithBsecInNextWakeUp)
	    {
	      alignIntReqWithBsecInNextWakeUp = 0;
	      timeOfIntExecutionInNextWakeUp = currentTime + 500000; // +0.5s, to generate the INT between 2 bsec cycles
	      intExecuteInNextWakeUp = 1;
	    }
	  }
	  if (cmdStartMeasurement)
	  {
		cmdStartMeasurement = 0;
		timeOfCmdStartMeasurement = get_timestamp_us();
	    //uart_buf_len = sprintf(uart_buf, "Master requests forced measurement. Time = %dms\r\n",(int)(get_timestamp_us()/1000));
	    //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
		mMeasurementReq = 1;
		if (firstCmdStartMeasurement == 0)
		{
		  mMeasurementReq = 0;
		  firstCmdStartMeasurement = 1;
		  HAL_Delay(100);
		  setup_bsec_bme680_interface();
		  HAL_Delay(100);
		}
		else
		{
		  timeEllapsedSinceLastMeasurement = (timeOfCmdStartMeasurement-timeULPStart)/1000; // in ms
		  if ((timeEllapsedSinceLastMeasurement > 290000) && (timeEllapsedSinceLastMeasurement < 301000)) // >290s & <301s, too close to next ULP start, wait until next ULP cycle is done.
		  {
			uart_buf_len = sprintf(uart_buf, "Master request for ULP_PLUS cycle delayed until new ULP cycle results are available, time elapsed since last ULP cycle = %dms\r\n",(int)timeEllapsedSinceLastMeasurement);
			HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
			DelayULPPStart = 1;
			mMeasurementReq = 0;
		  }
// following is removed because in the situations seen that this happens the ULP cycle is already done and an INT is not given anymore for this request
// there are other delays implemented to avoid that the INT is being given while a ULP cycle is ongoing.
//		  else if (timeEllapsedSinceLastMeasurement < 5000) // <5s, a ULP cycle could be happening right now... delay until this cycle is done.
//		  {
//			uart_buf_len = sprintf(uart_buf, "Master request for ULP_PLUS cycle delayed to avoid conflict with running ULP cycle,  time elapsed since last ULP cycle = %dms\r\n",(int)timeEllapsedSinceLastMeasurement);
//			HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
//			DelayULPPStart = 1;
//			mMeasurementReq = 0;
//		  }
		}
      }
	  if (mMeasurementReq && (currentTime >= timeOfCmdStartMeasurement) && (firstCmdStartMeasurement != 1))
	  {
		/* start ULP_PLUS CYCLE */
		bsec_library_return_t status = BSEC_OK;
		mMeasurementReq = 0;
		generateIntReq = 1;
		//timeOfIntReq = get_timestamp_us() + 4000000; // +4s
		timeDiffULPStart = get_timestamp_us() - timeULPStart;
		if (((timeDiffULPStart < 237000000) && (timeDiffULPStart > 58000000)) || (timeDiffULPStart > 300000000))  // do not request ULP_PLUS cycle if we know upfront if this will fail (a rejected request is causing delay and creates other issues).
		{
		  /* bsec_update_subscription() will be called in order to instruct BSEC to perform an extra measurement at the next possible time slot */
		  status = bme680_bsec_update_subscription(BSEC_SAMPLE_RATE_ULP_MEASUREMENT_ON_DEMAND);
		  /* The status code would tell us if the request was accepted. It will be rejected if the sensor is not already in
		   * ULP mode, or if the time difference between requests is too short. */
		  if (status != BSEC_OK)
		  {
		  	uart_buf_len = sprintf(uart_buf, "Master request for ULP_PLUS cycle rejected by BSEC, error code = %d. Last measurement data will be used. Time elapsed since last ULP measurement = %dms\r\n",(int)status,(int)(timeDiffULPStart/1000));
		    HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
		  	//timeOfIntReq += 5000000; // +4s
		  }
		  else
		  {
		  	uart_buf_len = sprintf(uart_buf, "Master request for ULP_PLUS cycle accepted by BSEC. Time elapsed since last ULP measurement = %dms\r\n",(int)(timeDiffULPStart/1000));
		  	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
		  	//timeOfIntReq += 3000000; // +10s (to make sure we wait after a BSEC cycle. After the BSEC cycle, timeofIntReq will be aligned with the end of the BSEC cycle + 1s)
		  }
		}
		else
		{
		  uart_buf_len = sprintf(uart_buf, "Master request for ULP_PLUS cycle not requested to BSEC. Last measurement data will be used. Time elapsed since last ULP measurement = %dms\r\n",(int)(timeDiffULPStart/1000));
		  HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
		  //timeOfIntReq += 3000000; // +4s
		}
      }
	  /* Compute how long we can sleep until we need to call bsec_sensor_control() next */
	  /* Time_stamp is converted from microseconds to nanoseconds first and then the difference to milliseconds */
	  //time_stamp_interval_ms = (sensor_settings.next_call - get_timestamp_us() * 1000) / 1000000;
	  //uart_buf_len = sprintf(uart_buf, "Time available to sleep before next bsec_sensor_control() = %d.\r\n",(int)time_stamp_interval_ms);
	  //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
	  //if (time_stamp_interval_ms > 0)
	  //{
	  //  sleep((uint32_t)time_stamp_interval_ms);
	  //}
//	}


//    if (mSetThresholds == 1)
//    {
//      sensorAPI.UpdateThreshold(aSlaveReceiveBuffer[1], aSlaveReceiveBuffer+1);
//    }
//
//	if (cmdGetMData == 1)
//	{
//    mDataReq = 1;
//	    pSlaveTransmitBuffer = (uint8_t *)(measurementData); //transmit of data wordt gesynchroniseerd met de meetcyclus
//	    ubSlaveNbDataToTransmit = 8;
//	}
//
//	if (cmdGetMNr == 1)
//	{
//	    mySlaveTransmitBuffer = M_NR;
//	    pSlaveTransmitBuffer = &mySlaveTransmitBuffer;
//		    ubSlaveNbDataToTransmit = 1;
//
//	}
//
//  	if (cmdDeviceType == 1)
//  	{
//  	  mySlaveTransmitBuffer = TYPE_BYTE;
//	    pSlaveTransmitBuffer = &mySlaveTransmitBuffer;
//	    ubSlaveNbDataToTransmit = 1;
//  	}
//
//	  if (cmdPoll == 1)
//	  {
//			//uart_buf_len = sprintf(uart_buf, "Master polls address. Time = %dms\r\n",(int)(get_timestamp_us()/1000));
//		    //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
//			mySlaveTransmitBuffer = DEFAULT_ACK;
//		    pSlaveTransmitBuffer = &mySlaveTransmitBuffer;
//		    ubSlaveNbDataToTransmit = 1;
//
//	  }



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV4;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_HSI;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */




/**********************************************************************************************************************/
/* functions */
/**********************************************************************************************************************/

/**
  * @brief  Slave Address Match callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  TransferDirection: Master request Transfer Direction (Write/Read), value of @ref I2C_XferOptions_definition
  * @param  AddrMatchCode: Address Match Code
  * @retval None
  */
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
  char uart_buf[200];
  int uart_buf_len;
  //uart_buf_len = sprintf(uart_buf, "Master request. AddrMatchCode = 0x%02X\r\n",AddrMatchCode >> 1);
  //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
  if(AddrMatchCode >> 1 == I2C_ADDRESS)
  {
    uwTransferDirection = TransferDirection;
    /* First of all, check the transfer direction to call the correct Slave Interface */
    if(uwTransferDirection == I2C_DIRECTION_TRANSMIT) // Slave receives data from Master
    {
      if(HAL_I2C_Slave_Seq_Receive_IT(&hi2c1, &aSlaveReceiveBuffer[ubSlaveReceiveIndex], 1, I2C_FIRST_FRAME) != HAL_OK)
      {
        uart_buf_len = sprintf(uart_buf, "Error HAL_I2C_Slave_Sequential_Receive_IT.\r\n");
        HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
        Error_Handler();
      }
      ubSlaveReceiveIndex++;
    }
    else // Slave to send data to Master
    {
      if(HAL_I2C_Slave_Seq_Transmit_IT(&hi2c1, pSlaveTransmitBuffer, ubSlaveNbDataToTransmit, I2C_LAST_FRAME) != HAL_OK)
      {
        uart_buf_len = sprintf(uart_buf, "Error HAL_I2C_Slave_Sequential_Transmit_IT.\r\n");
        HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
        Error_Handler();
      }
      else
      {
        //uart_buf_len = sprintf(uart_buf, "Data sent from Slave.\r\n");
        //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
        ubSlaveReceiveIndex = 0;
      }
    }
  }
  else
  {
    /* Call Error Handler, Wrong Address Match Code */
    uart_buf_len = sprintf(uart_buf, "Wrong Address Match Code: 0x%02X\r\n",(AddrMatchCode >> 1));
    HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);

    Error_Handler();
  }
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  I2cHandle: I2C handle
  * @note   This example shows a simple way to report end of IT Rx transfer, and
  *         you can add your own implementation.
  * @retval None
  */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *I2cHandle)
{
  char uart_buf[200];
  int uart_buf_len;
  //uart_buf_len = sprintf(uart_buf, "HAL_I2C_SlaveRxCpltCallback. Received byte: 0x%02X\r\n",aSlaveReceiveBuffer[ubSlaveReceiveIndex-1]);
  //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
  /* Check Command code receive previously */
  /* If data received match with a Internal Command Code, set the associated index */
  /* Which will use for Tranmission process if requested by Master */
  if (uwTransferDirection == I2C_DIRECTION_TRANSMIT) // Slave receives data from Master
  {
    //uart_buf_len = sprintf(uart_buf, "Received command: 0x%02X\r\n",aSlaveReceiveBuffer[ubSlaveReceiveIndex-1]);
    //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
    switch (aSlaveReceiveBuffer[0])
    {
      // POLL
	  case CMD_POLL: // master polls address -> respond with ack
	  {
	    // Master reset cycle begins. Set following variables to 0:
		MasterReset = 0;
		firstCmdStartMeasurement = 0;
		MasterCycleCounter = 0;
		generateIntReq = 0;
		mMeasurementReq = 0;

		cmdPoll = 1;
		//uart_buf_len = sprintf(uart_buf, "Master polls address. Time = %dms\r\n",(int)(get_timestamp_us()/1000));
	    //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
 		mySlaveTransmitBuffer = DEFAULT_ACK;
	    pSlaveTransmitBuffer = &mySlaveTransmitBuffer;
	    ubSlaveNbDataToTransmit = 1;
      } break;
      // TYPE
      case CMD_DEVICE_TYPE: // master requests sensor type -> respond with type
      {
  		//uart_buf_len = sprintf(uart_buf, "Master requests sensor type. Time = %dms\r\n",(int)(get_timestamp_us()/1000));
  	    //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
    	cmdDeviceType = 1;
    	mySlaveTransmitBuffer = TYPE_BYTE;
	    pSlaveTransmitBuffer = &mySlaveTransmitBuffer;
  	    ubSlaveNbDataToTransmit = 1;
      } break;
      // NR OF METRICS
      case CMD_GET_M_NR: // master requests measurement data length -> respond with length
      {
    	//uart_buf_len = sprintf(uart_buf, "Master requests measurement data length. Time = %dms\r\n",(int)(get_timestamp_us()/1000));
  	    //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
    	cmdGetMNr = 1;
        mySlaveTransmitBuffer = M_NR;
	    pSlaveTransmitBuffer = &mySlaveTransmitBuffer;
   	    ubSlaveNbDataToTransmit = 1;
      } break;
      // MEASURE
      case CMD_START_MEASUREMENT: // master forces measurement -> respond with ack
      {
      	/* Master requests measurement */
    	cmdStartMeasurement = 1;
//    	startFirstMeasurement = 1;

//        uart_buf_len = sprintf(uart_buf, "Master requests forced measurement. Time = %dms\r\n",(int)(get_timestamp_us()/1000));
//    	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
//    	firstCmdStartMeasurement = 1;
//    	mMeasurementReq = 1;
//    	timeOfCmdStartMeasurement = get_timestamp_us();
//        timeEllapsedSinceLastMeasurement = (timeOfCmdStartMeasurement-timeULPStart)/1000; // in ms
//  	    if (timeEllapsedSinceLastMeasurement > 290000) // 290s, too close to next ULP start, wait until next ULP cycle is done.
//  	    {
//  	      //timeDelayULPPStart = 304000 - timeEllapsedSinceLastMeasurement;
//      	  //timeOfCmdStartMeasurement = get_timestamp_us() +
//          uart_buf_len = sprintf(uart_buf, "Interrupt to master delayed until new ULP measurement results are available, time elapsed since last ULP cycle = %dms\r\n",(int)timeEllapsedSinceLastMeasurement);
//      	  HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
//      	  DelayULPPStart = 1;
//      	  mMeasurementReq = 0;
//  	    }
//  	    else if (timeEllapsedSinceLastMeasurement < 3000) // 3s, a ULP cycle could be happening right now... delay until this cycle is done.
//  	    {
//          uart_buf_len = sprintf(uart_buf, "Interrupt to master delayed to avoid conflict with running ULP measurement,  time elapsed since last ULP cycle = %dms\r\n",(int)timeEllapsedSinceLastMeasurement);
//          HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
//          //timeOfCmdStartMeasurement += 5000000; // + 5s
//      	  DelayULPPStart = 1;
//      	  mMeasurementReq = 0;
//  	    }
//        //sensorAPI.Measure(); // start of measurement wordt gesynchroniseerd met de meetcyclus
      } break;
      // GET DATA
      case CMD_GET_M_DATA: // master requests measurement data -> send data
      {
    	cmdGetMData = 1;
        mDataReq = 1;
  	    pSlaveTransmitBuffer = (uint8_t *)(measurementData); //transmit of data wordt gesynchroniseerd met de meetcyclus
   	    ubSlaveNbDataToTransmit = 8;

        //uart_buf_len = sprintf(uart_buf, "Master requests measurement data. Time = %dms\r\n",(int)(get_timestamp_us()/1000));
        //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
      } break;
      // INT TOGGLE
      case CMD_INT_TOGGLE: //toggle the INT line
      {
        //uart_buf_len = sprintf(uart_buf, "Master toggles INT line. Time = %dms\r\n",(int)(get_timestamp_us()/1000));
        //HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
//    	timeOfCmdIntToggleByMaster = get_timestamp_us();
    	cmdIntToggleByMaster = 1;
//    	startFirstMeasurement = 1;

        if (Ready == 0)
        {
          HAL_GPIO_WritePin(INT_GPIO_Port, INT_Pin, GPIO_PIN_RESET);
          Ready = 1;
        }
        else
        {
          HAL_GPIO_WritePin(INT_GPIO_Port, INT_Pin, GPIO_PIN_SET);
          Ready = 0;

        }
      } break;
      // SET_THRESHOLDS
      case CMD_SET_THRESHOLDS: //read thresholds
      {
        if(HAL_I2C_Slave_Seq_Receive_IT(I2cHandle, &aSlaveReceiveBuffer[ubSlaveReceiveIndex], 1, I2C_NEXT_FRAME) != HAL_OK)
	    {
	      uart_buf_len = sprintf(uart_buf, "Read thresholds Error receiving bytes.\r\n");
	      HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
	      Error_Handler();
		}
	    if(ubSlaveReceiveIndex == 6)
	    {
	      mSetThresholds = 1;
	      sensorAPI.UpdateThreshold(aSlaveReceiveBuffer[1], aSlaveReceiveBuffer+1);
	    }
	    ubSlaveReceiveIndex++;
      } break;
      // else receive more bytes from Master
	  default:
	  {
        if(HAL_I2C_Slave_Seq_Receive_IT(I2cHandle, &aSlaveReceiveBuffer[ubSlaveReceiveIndex], 1, I2C_NEXT_FRAME) != HAL_OK)
	    {
  	      uart_buf_len = sprintf(uart_buf, "Unknown command. Error receiving bytes.\r\n");
  	      HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
	      Error_Handler();
		}
        else
        {
   	      uart_buf_len = sprintf(uart_buf, "Unknown command.\r\n");
   	      HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
        }
		ubSlaveReceiveIndex++;
	  } break;
    }
  }

//  /*##-2- Put I2C peripheral in Listen address match code process ##########*/
//	/* This action will allow I2C periphal to able to treat Master request when
//	   necessary depending of transfer direction requested by Master */
//	if(HAL_I2C_EnableListen_IT(&hi2c1) != HAL_OK)
//	{
//	  /* Transfer error in reception process */
//	  //Error_Handler();
// 	  uart_buf_len = sprintf(uart_buf, "HAL_I2C_EnableListen_IT(&hi2c1) error (initiated after callback).\r\n");
// 	  HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
//	}

}

/**
  * @brief  Tx Transfer completed callback.
  * @param  I2cHandle: I2C handle
  * @note   This example shows a simple way to report end of IT Tx transfer, and
  *         you can add your own implementation.
  * @retval None
  */
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *I2cHandle)
{
  ubSlaveReceiveIndex = 0; // reset buffer
}

/**
  * @brief  Listen Complete callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
  ubSlaveReceiveIndex = 0; // reset buffer
}

/*!
 * @brief           Write operation in either I2C or SPI
 *
 * param[in]        dev_addr        I2C or SPI device address
 * param[in]        reg_addr        register address
 * param[in]        reg_data_ptr    pointer to the data to be written
 * param[in]        data_len        number of bytes to be written
 *
 * @return          result of the bus communication function
 */
int8_t bus_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data_ptr, uint16_t data_len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    HAL_StatusTypeDef HAL_Status;
    HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_Status = HAL_SPI_Transmit(&hspi1, (uint8_t *)&reg_addr, 1, 100);
	if (HAL_Status != HAL_OK)
	{
		rslt = 1;
	}
	HAL_Status = HAL_SPI_Transmit(&hspi1, (uint8_t *)reg_data_ptr,data_len,100);
	if (HAL_Status != HAL_OK)
	{
		rslt = 1;
	}
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
    return rslt;
}

/*!
 * @brief           Read operation in either I2C or SPI
 *
 * param[in]        dev_addr        I2C or SPI device address
 * param[in]        reg_addr        register address
 * param[out]       reg_data_ptr    pointer to the memory to be used to store the read data
 * param[in]        data_len        number of bytes to be read
 *
 * @return          result of the bus communication function
 */
int8_t bus_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data_ptr, uint16_t data_len)
{
	int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    HAL_StatusTypeDef HAL_Status;
    HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);
	HAL_Status = HAL_SPI_Transmit(&hspi1, (uint8_t *)&reg_addr, 1, 100);
	if (HAL_Status != HAL_OK)
	{
		rslt = 1;
	}
	HAL_Status = HAL_SPI_Receive(&hspi1, (uint8_t *)reg_data_ptr, data_len, 100);
	if (HAL_Status != HAL_OK)
	{
		rslt = 1;
	}
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
    return rslt;
}

/*!
 * @brief           System specific implementation of sleep function
 *
 * @param[in]       t_ms    time in milliseconds
 *
 * @return          none
 */
void sleep(uint32_t t_ms)
{
    while(t_ms > 0)
    {
    	HAL_Delay(1);
    	t_ms--;
    }
}

/*!
 * @brief           Capture the system time in microseconds
 *
 * @return          system_current_time    current system timestamp in microseconds
 */
uint64_t get_timestamp_us()
{
	static uint64_t microseconds_since_start = 0;
    microseconds_since_start += (uint64_t)(uwTick * 1000 - (uint32_t)(microseconds_since_start));
    return microseconds_since_start;
}

/*!
 * @brief           Handling of the ready outputs
 *
 * @param[in]       timestamp       time in nanoseconds
 * @param[in]       iaq             IAQ signal
 * @param[in]       iaq_accuracy    accuracy of IAQ signal
 * @param[in]       temperature     temperature signal
 * @param[in]       humidity        humidity signal
 * @param[in]       pressure        pressure signal
 * @param[in]       raw_temperature raw temperature signal
 * @param[in]       raw_humidity    raw humidity signal
 * @param[in]       gas             raw gas sensor signal
 * @param[in]       bsec_status     value returned by the bsec_do_steps() call
 *
 * @return          none
 */
void output_ready(int64_t timestamp, float iaq, uint8_t iaq_accuracy, float temperature, float humidity,
     float pressure, float raw_temperature, float raw_humidity, float gas, bsec_library_return_t bsec_status,
     float static_iaq, float co2_equivalent, float breath_voc_equivalent)
{
  char uart_buf[200];
  int uart_buf_len;

//  cycletimeBSEC = (get_timestamp_us()-currentTime)/1000;
//  uart_buf_len = sprintf(uart_buf, "Duration BSEC cycle before conversion and print =  %dms\r\n",(int)cycletimeBSEC);
//  HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);


  // convert readings to 16-bit value
  temp16 = (uint16_t)((temperature*100)+5000);
  pres16 = (uint16_t)((pressure+0.05f)/100);
  iaq16 = ((uint16_t)(iaq)) & (0x0000FFFF);
  humi16 = (uint16_t)((humidity+0.05f)*100);
  iaqacc = iaq_accuracy;
  // copy readings to byte buffer
  if (__HAL_I2C_GET_FLAG(&hi2c1,I2C_FLAG_BUSY))
  {
	uart_buf_len = sprintf(uart_buf, "HAL_I2C_BUSY! No update of measurement data at this moment!\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
  }
  else
  {
	measurementData[METRIC_TEMPERATURE*2] = (temp16 >> 8);
	measurementData[1+METRIC_TEMPERATURE*2] = (temp16 & 0xFF);
	measurementData[METRIC_PRESSURE*2] = (pres16 >> 8);
	measurementData[1+METRIC_PRESSURE*2] = (pres16 & 0xFF);
	measurementData[METRIC_IAQ*2] = (iaq16 >> 8);
	measurementData[1+METRIC_IAQ*2] = (iaq16 & 0xFF);
	measurementData[METRIC_HUMIDITY*2] = (humi16 >> 8);
	measurementData[1+METRIC_HUMIDITY*2] = (humi16 & 0xFF);
  }

//  cycletimeBSEC = (get_timestamp_us()-currentTime)/1000;
//  uart_buf_len = sprintf(uart_buf, "Duration BSEC cycle before LED =  %dms\r\n",(int)cycletimeBSEC);
//  HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);

  processLed = iaq_accuracy;

//  switch (iaq_accuracy)
//  {
//    case 0: // start_up status
//	{
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//	} break;
//	case 1: // start_up status
//	{
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//    } break;
//	case 2: // Calibrating
//	{
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//	} break;
//	case 3: // Calibrated!
//	{
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
//	  HAL_Delay(50);
//	  HAL_GPIO_WritePin(INT_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//	} break;
//  }


  uart_buf_len = sprintf(uart_buf, "SPC = %d, Temp = %5.2f °C, - 0x%2X, Press = %6.2f mbar, - 0x%2X, IAQ = %5.2f - 0x%2X, Hum = %5.2f %%, - 0x%2X, INT = %X, mDataReq = %X, IAQ_acc = %d\r\n",(int)currentTime/1000,temperature,temp16,pressure/100,pres16,iaq,iaq16,humidity,humi16,generateIntReq,mDataReq,iaq_accuracy);
  HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
  /* Master requests measurement */
}

/*!
 * @brief           Load previous library state from non-volatile memory
 *
 * @param[in,out]   state_buffer    buffer to hold the loaded state string
 * @param[in]       n_buffer        size of the allocated state buffer
 *
 * @return          number of bytes copied to state_buffer
 */
uint32_t state_load(uint8_t *state_buffer, uint32_t n_buffer)
{
  // ...
  // Load a previous library state from non-volatile memory, if available.
  //
  // Return zero if loading was unsuccessful or no state was available,
  // otherwise return length of loaded state string.
  // ...
  char uart_buf[200];
  int uart_buf_len;
  Address = DATA_EEPROM_BASE;
  /* Check if the programmed data is OK
      memoryProgramStatus = 0: no bsec state data available
      memoryProgramStatus != 0: bsec state data available ******/
  int32_t i = 0;
  int8_t memoryProgramStatus = 0;
  while (i < n_buffer)
  {
    if (*(__IO uint8_t *)(Address) != 0)
    {
	  memoryProgramStatus++;
    }
    Address++;
    i++;
  }
  /*Check if there is an issue to load the data*/
  if (memoryProgramStatus != 0)
  {
	Address = DATA_EEPROM_BASE;
	i = 0;
	while (i < n_buffer)
	{
	  state_buffer[i] = *(__IO uint8_t *)(Address);
	  Address++;
	  i++;
	}
	uart_buf_len = sprintf(uart_buf, "Bsec state DATA available and loaded. n_buffer length = %d.\r\n",(int)n_buffer);
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
	return n_buffer;
  }
  else
  {
	uart_buf_len = sprintf(uart_buf, "No bsec state DATA available.\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
	return 0;
  }
  return 0;
}

///*!
// * @brief           Save library state to non-volatile memory
// *
// * @param[in]       state_buffer    buffer holding the state to be stored
// * @param[in]       length          length of the state string to be stored
// *
// * @return          none
// */
//void state_save_partial(const uint8_t *state_buffer, uint32_t length, uint8_t saveBsecState)
//{
//  char uart_buf[150];
//  int uart_buf_len;
//  /* Unlock the DATA EEPROM Flash to enable the flash control register access *************/
//  HAL_FLASHEx_DATAEEPROM_Unlock();
//  /* Erase the DATA EEPROM Flash area word by word (area defined by length) ***********/
//  int32_t i = length;
//  int32_t Address = DATA_EEPROM_BASE + 12*(saveBsecState-1);
//  int8_t erase_OK = 1;
//  int8_t program_OK = 1;
//  int8_t memoryProgramStatus = 0;
//  while (i > 0)
//  {
//    if (HAL_FLASHEx_DATAEEPROM_Erase(Address) == HAL_OK)
//    {
////      *(__IO uint32_t *) Address = 0x00000000U;
//      Address = Address + 4;
//      i = i-4;
//    }
//    else
//    {
//      /* Error occurred while erasing DATA EEPROM Flash memory. */
//      uart_buf_len = sprintf(uart_buf, "DATA EEPROM Erase error!\r\n");
//      HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
//      erase_OK = 0;
//    }
//  }
//  /* Program the DATA EEPROM Flash area byte by byte (area defined by length) ***********/
//  if (erase_OK)
//  {
//	Address = DATA_EEPROM_BASE + 10*(saveBsecState-1);
//	i = 0;
//	while (i < length)
//	{
//	  if (HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, Address, state_buffer[10*(saveBsecState-1) + i]) == HAL_OK)
//	  {
////		*(__IO uint8_t *)Address = (uint8_t) state_buffer[i];
//		Address++;
//	    i++;
//	  }
//	  else
//	  {
//	    /* Error occurred while writing DATA EEPROM Flash memory. */
//	    uart_buf_len = sprintf(uart_buf, "DATA EEPROM Write error!\r\n");
//	    HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
//	    program_OK = 0;
//	  }
//	}
//  }
//  /* Lock the DATA EEPROM Flash to disable the flash control register access (recommended
//     to protect the FLASH memory against possible unwanted operation) *********/
//  HAL_FLASHEx_DATAEEPROM_Lock();
//  /* Check if the programmed data is OK
//      memoryProgramStatus = 0: data programmed correctly
//      memoryProgramStatus != 0: number of words not programmed correctly ******/
//  if (program_OK)
//  {
//	Address = DATA_EEPROM_BASE + 10*(saveBsecState-1);
//	i = 0;
//	while (i < length)
//	{
//	  if (state_buffer[10*(saveBsecState-1)+i] != *(__IO uint8_t *)(Address))
//	  {
//		memoryProgramStatus++;
//	  }
//	  Address++;
//	  i++;
//	}
//  }
//  /*Check if verification is OK*/
//  if (memoryProgramStatus != 0)
//  {
//	uart_buf_len = sprintf(uart_buf, "DATA EEPROM Verification error!\r\n");
//	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
//  }
//  else
//  {
////	uart_buf_len = sprintf(uart_buf, "Library state (%d bytes) correctly saved to DATA EEPROM.\r\n",length);
////    HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
//  }
//}

/*!
 * @brief           Save library state to non-volatile memory
 *
 * @param[in]       state_buffer    buffer holding the state to be stored
 * @param[in]       length          length of the state string to be stored
 *
 * @return          none
 */
void state_save(const uint8_t *state_buffer, uint32_t length)
{
  char uart_buf[200];
  int uart_buf_len;
  /* Unlock the DATA EEPROM Flash to enable the flash control register access *************/
  HAL_FLASHEx_DATAEEPROM_Unlock();
  /* Erase the DATA EEPROM Flash area word by word (area defined by length) ***********/
  Address = DATA_EEPROM_BASE;
  int32_t i = length;
//  int32_t i = 12;
  int8_t erase_OK = 1;
  int8_t program_OK = 1;
  int8_t memoryProgramStatus = 0;
  while (i > -4)
  {
    if (HAL_FLASHEx_DATAEEPROM_Erase(Address) == HAL_OK)
    {
      *(__IO uint32_t *) Address = 0x00000000U;
      Address = Address + 4;
      i = i-4;
    }
    else
    {
      /* Error occurred while erasing DATA EEPROM Flash memory. */
      uart_buf_len = sprintf(uart_buf, "DATA EEPROM Erase error!\r\n");
      HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
      erase_OK = 0;
    }
  }
  /* Program the DATA EEPROM Flash area byte by byte (area defined by length) ***********/
  if (erase_OK)
  {
	Address = DATA_EEPROM_BASE;
	i = 0;
	while (i < length)
//	while (i < 10)
	{
	  if (HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE, Address, state_buffer[i]) == HAL_OK)
	  {
		*(__IO uint8_t *)Address = (uint8_t) state_buffer[i];
		Address++;
	    i++;
	  }
	  else
	  {
	    /* Error occurred while writing DATA EEPROM Flash memory. */
	    uart_buf_len = sprintf(uart_buf, "DATA EEPROM Write error!\r\n");
	    HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
	    program_OK = 0;
	  }
	}
  }
  /* Lock the DATA EEPROM Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASHEx_DATAEEPROM_Lock();
  /* Check if the programmed data is OK
      memoryProgramStatus = 0: data programmed correctly
      memoryProgramStatus != 0: number of words not programmed correctly ******/
  if (program_OK)
  {
	Address = DATA_EEPROM_BASE;
	i = 0;
	while (i < length)
	{
	  if (state_buffer[i] != *(__IO uint8_t *)(Address))
	  {
		memoryProgramStatus++;
	  }
	  Address++;
	  i++;
	}
  }
  /*Check if verification is OK*/
  if (memoryProgramStatus != 0)
  {
	uart_buf_len = sprintf(uart_buf, "DATA EEPROM Verification error!\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
  }
  else
  {
	uart_buf_len = sprintf(uart_buf, "Library state (%d bytes) correctly saved to DATA EEPROM.\r\n",(int)length);
    HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
  }
}

/*!
 * @brief           Load library config from non-volatile memory
 *
 * @param[in,out]   config_buffer    buffer to hold the loaded state string
 * @param[in]       n_buffer        size of the allocated state buffer
 *
 * @return          number of bytes copied to config_buffer
 */
uint32_t config_load(uint8_t *config_buffer, uint32_t n_buffer)
{
    //
    // Load generic_33v_3s_4d library config from non-volatile memory, if available.
    //
	memcpy(config_buffer,bsec_config_iaq, sizeof(bsec_config_iaq));
    // Return zero if loading was unsuccessful or no config was available,
    // otherwise return length of loaded config string.
    // ...
    return sizeof(bsec_config_iaq);
}

/*!
 * @brief       Main function which configures BSEC library and then reads and processes the data from sensor based
 *              on timer ticks
 *
 * @return      result of the processing
 */
int setup_bsec_bme680_interface()
{
    return_values_init ret;
	bsec_version_t  version;
	char uart_buf[200];
	int uart_buf_len;

    /* Call to the function which initializes the BSEC library
     * Switch on low-power mode and provide no temperature offset */
    ret = bsec_iot_init(BSEC_SAMPLE_RATE_ULP, 0.5f, bus_write, bus_read, sleep, state_load, config_load);
    if (ret.bme680_status)
    {
        /* Could not intialize BME680 */
    	uart_buf_len = sprintf(uart_buf, "Error while initializing BME680. bme680_status = %d\r\n",ret.bme680_status);
    	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
        return (int)ret.bme680_status;
    }
    else
    {
        /* BME680 initialized */
    	uart_buf_len = sprintf(uart_buf, "BME680 initialized.\r\n");
    	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
    	if (ret.bsec_status)
    	{
    		/* Could not intialize BSEC library */
    		uart_buf_len = sprintf(uart_buf, "Error while initializing BSEC library. bsec_status = %d\r\n",ret.bsec_status);
    		HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
    		return (int)ret.bsec_status;
    	}
    	else
    	{
    		/* BSEC library initialized */
        	uart_buf_len = sprintf(uart_buf, "BSEC initialized.\r\n");
        	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
    		bsec_get_version(&version);
    		uart_buf_len = sprintf(uart_buf, "BSEC version: %d.%d.%d.%d\n",version.major, version.minor, version.major_bugfix, version.minor_bugfix);
    		HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
    	}
    }


//    /* Call to endless loop function which reads and processes data based on sensor settings */
//    /* State is saved every 10.000 samples, which means every 10.000 * 3 secs = 500 minutes  */
//    bsec_iot_loop(sleep, get_timestamp_us, output_ready, state_save, 10000);

    return 0;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	//	char uart_buf[100];
	//	int uart_buf_len;
	//	uart_buf_len = sprintf(uart_buf, "Error handler.\r\n");
	//	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buf, uart_buf_len, 100);
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
