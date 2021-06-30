/*  ____  ____      _    __  __  ____ ___
 * |  _ \|  _ \    / \  |  \/  |/ ___/ _ \
 * | | | | |_) |  / _ \ | |\/| | |  | | | |
 * | |_| |  _ <  / ___ \| |  | | |__| |_| |
 * |____/|_| \_\/_/   \_\_|  |_|\____\___/
 *                           research group
 *                             dramco.be/
 *
 *  KU Leuven - Technology Campus Gent,
 *  Gebroeders De Smetstraat 1,
 *  B-9000 Gent, Belgium
 *
 *         File: veml7700.c
 *      Created: 2021-06-24
 *       Author: Jona Cappelle
 *      Version: 1.0
 *
 *  Description: Interface 
 *      with VEML7700 light sensor
 *
 */

#include "veml7700.h"
#include <string.h>


void veml7700_power(bool enable)
{
    switch (enable){
        case 1:
            // Set pin high to power VEML7700
            VEML7700_PWR_SetDigitalMode();
            VEML7700_PWR_SetDigitalOutput();
            VEML7700_PWR_SetHigh();
          break;
        case 0:
            // Set pin low to cut power to VEML7700
            VEML7700_PWR_SetDigitalMode();
            VEML7700_PWR_SetDigitalOutput();
            VEML7700_PWR_SetLow(); 
          break;
        default:
            // Default to off
            VEML7700_PWR_SetDigitalMode();
            VEML7700_PWR_SetDigitalOutput();
            VEML7700_PWR_SetLow();
    }
    
    // Small delay to let voltage stabilize
    __delay_ms(100);
}

void veml7700_init(veml7700_settings const * p_config, veml7700_data * p_data)
{
    // Init I2C interface
    I2C2_Initialize();
    
    // Configure sensor
    veml7700_configure(p_config);
}

void veml7700_configure(veml7700_settings const * p_config)
{
    // Reset settings
    // Start in a known state
    veml7700_soft_reset();
    
    // Set Gain
    veml7700_setConf_ALS_GAIN(p_config->gain);

    // Set Integration Time
    veml7700_setConf_ALS_IT(p_config->integration_time);
    
    // Set Persistence
    veml7700_setConf_ALS_PERS(p_config->persistence);
    
    // Set Interrupts
    veml7700_setConf_ALS_INT_EN(p_config->interrupts);
    
    // Set Power save
    veml7700_setPowerSaving(p_config->powersave_en, p_config->powersave);
    
    // Set Thresholds
    veml7700_setALS_WH(p_config->threshold_high);
    veml7700_setALS_WL(p_config->threshold_low);
}

void veml7700_deinit()
{
    // De-init I2C
    
    // De-init veml7700
    
    // Disable power to veml7700

}

void veml7700_soft_reset()
{
    // Reset value config register
    uint8_t data[2] = { 0x00, 0x00 };
    // Send to config register
    veml7700_write(VEML7700_ALS_CONFIG, data, 2);// Send to config register
}


float veml7700_raw_to_lux(uint16_t raw)
{
    
}

void veml7700_read(uint8_t dataAddress, uint8_t *pData, uint16_t nCount)
{    
    uint16_t slaveDeviceAddress = VEML7700_I2CADDR_DEFAULT;
   
    I2C2_MESSAGE_STATUS status;
    I2C2_TRANSACTION_REQUEST_BLOCK readTRB[2];
    uint8_t     writeBuffer[3];
    uint16_t    timeOut;

    // this initial value is important
    status = I2C2_MESSAGE_PENDING;

    // build the write buffer first
    // starting address of the EEPROM memory
//    writeBuffer[0] = (dataAddress >> 8);                        // high address
//    writeBuffer[1] = (uint8_t)(dataAddress);                    // low low address

    // we need to create the TRBs for a random read sequence to the EEPROM
    // Build TRB for sending address
    I2C2_MasterWriteTRBBuild(   &readTRB[0],
                                    &dataAddress,
                                    1,
                                    slaveDeviceAddress);
    // Build TRB for receiving data
    I2C2_MasterReadTRBBuild(    &readTRB[1],
                                    pData,
                                    nCount,
                                    slaveDeviceAddress);

    timeOut = 0;

    while(status != I2C2_MESSAGE_FAIL)
    {
        // now send the transactions
        I2C2_MasterTRBInsert(2, readTRB, &status);

        // wait for the message to be sent or status has changed.
        while(status == I2C2_MESSAGE_PENDING);

        if (status == I2C2_MESSAGE_COMPLETE)
            break;

        // if status is  I2C2_MESSAGE_ADDRESS_NO_ACK,
        //               or I2C2_DATA_NO_ACK,
        // The device may be busy and needs more time for the last
        // write so we can retry writing the data, this is why we
        // use a while loop here

        // check for max retry and skip this byte
        if (timeOut == SLAVE_I2C_GENERIC_RETRY_MAX)
            break;
        else
            timeOut++;

    }
}

// 10 bytes max transaction size
void veml7700_write(uint8_t addr, uint8_t* data, uint8_t len)
{
    uint8_t ret;
    uint16_t    timeOut;
    
    uint8_t temp[11];
    temp[0] = addr;
    memcpy(&temp[1], data, len);
    len++;
    
    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;
    
    // Now it is possible that the slave device will be slow.
    // As a work around on these slaves, the application can
    // retry sending the transaction
    timeOut = 0;
    while(status != I2C2_MESSAGE_FAIL)
    {
        // write data over I2C bus
        I2C2_MasterWrite(temp, len, VEML7700_I2CADDR_DEFAULT, &status);
    
        // wait for the message to be sent or status has changed.
        while(status == I2C2_MESSAGE_PENDING);

        if (status == I2C2_MESSAGE_COMPLETE)
            break;

        // if status is  I2C2_MESSAGE_ADDRESS_NO_ACK,
        //               or I2C2_DATA_NO_ACK,
        // The device may be busy and needs more time for the last
        // write so we can retry writing the data, this is why we
        // use a while loop here

        // check for max retry and skip this byte
        if (timeOut == VEML7700_RETRY_MAX)
            break;
        else
            timeOut++;
    }
    
    // exit if the last transaction failed
    if (status == I2C2_MESSAGE_FAIL)
    {
        ret = 0;
//        break;
    }
    
}

void veml7700_setConf_ALS_GAIN(VEML7700_GAIN gain)
{    
    // Get config register value
    uint16_t data = veml7700_getALSConf();
    
    //Set all data in the bitmask to zero
    data &= ~(VEML7700_ALS_GAIN_MASK);
    
    // Bitmask with gain setting
    switch (gain){
        case VEML7700_GAIN_X1:
            data |= ( (VEML7700_GAIN_1 << 11) & VEML7700_ALS_GAIN_MASK);
            break;

        case VEML7700_GAIN_X2:
            data |= ( (VEML7700_GAIN_2 << 11) & VEML7700_ALS_GAIN_MASK);
            break;
          
        case VEML7700_GAIN_1X8:
            data |= ( (VEML7700_GAIN_1_8 << 11) & VEML7700_ALS_GAIN_MASK);
            break;

        case VEML7700_GAIN_1X4:
            data |= ( (VEML7700_GAIN_1_4 << 11) & VEML7700_ALS_GAIN_MASK);
            break;
          
        default:
            data |= ( (VEML7700_GAIN_1 << 11) & VEML7700_ALS_GAIN_MASK);  
            break;
    }
    
    // Write modified parameters back to config register
    veml7700_setALSConf(data);   
}

void veml7700_setConf_ALS_IT(VEML7700_IT time)
{
    // Get config register value
    uint16_t data = veml7700_getALSConf();
    
    //Set all data in the bitmask to zero
    data &= ~(VEML7700_ALS_INT_MASK);
    
    // Bitmask with gain setting
    switch (time){
        case VEML7700_INTEGRATION_TIME_100MS:
            data |= ( (VEML7700_IT_100MS << 6) & VEML7700_ALS_INT_MASK);
            break;

        case VEML7700_INTEGRATION_TIME_200MS:
            data |= ( (VEML7700_IT_200MS << 6) & VEML7700_ALS_INT_MASK);
            break;
          
        case VEML7700_INTEGRATION_TIME_400MS:
            data |= ( (VEML7700_IT_400MS << 6) & VEML7700_ALS_INT_MASK);
            break;

        case VEML7700_INTEGRATION_TIME_800MS:
            data |= ( (VEML7700_IT_800MS << 6) & VEML7700_ALS_INT_MASK);
            break;
            
        case VEML7700_INTEGRATION_TIME_50MS:
            data |= ( (VEML7700_IT_50MS << 6) & VEML7700_ALS_INT_MASK);
            break;
            
        case VEML7700_INTEGRATION_TIME_25MS:
            data |= ( (VEML7700_IT_25MS << 6) & VEML7700_ALS_INT_MASK);
            break;
          
        default:
            data |= ( (VEML7700_IT_100MS << 6) & VEML7700_ALS_INT_MASK);  
            break;
    }
    
    // Write modified parameters back to config register
    veml7700_setALSConf(data);
}

void veml7700_setConf_ALS_PERS(VEML7700_PERS pers)
{    
    // Get config register value
    uint16_t data = veml7700_getALSConf();
    
    //Set all data in the bitmask to zero
    data &= ~(VEML7700_ALS_PERS_MASK);
    
    // Bitmask with gain setting
    switch (pers){
        case VEML7700_PERSISTENCE_1:
            data |= ( (VEML7700_PERS_1 << 4) & VEML7700_ALS_PERS_MASK);
            break;

        case VEML7700_PERSISTENCE_2:
            data |= ( (VEML7700_PERS_2 << 4) & VEML7700_ALS_PERS_MASK);
            break;
          
        case VEML7700_PERSISTENCE_4:
            data |= ( (VEML7700_PERS_4 << 4) & VEML7700_ALS_PERS_MASK);
            break;

        case VEML7700_PERSISTENCE_8:
            data |= ( (VEML7700_PERS_8 << 4) & VEML7700_ALS_PERS_MASK);
            break;
          
        default:
            data |= ( (VEML7700_PERS_1 << 4) & VEML7700_ALS_PERS_MASK);  
            break;
    }
    
    // Write modified parameters back to config register
    veml7700_setALSConf(data);   
}


void veml7700_setConf_ALS_INT_EN(VEML7700_INT i)
{    
    // Get config register value
    uint16_t data = veml7700_getALSConf();
    
    //Set all data in the bitmask to zero
    data &= ~(VEML7700_ALS_INT_EN_MASK);
    
    // Bitmask with gain setting
    switch (i){
        case VEML7700_INTERRUPT_DISABLE:
            data |= ( (VEML7700_ALS_INT_DISABLE << 1) & VEML7700_ALS_INT_EN_MASK);
            break;

        case VEML7700_INTERRUPT_ENABLE:
            data |= ( (VEML7700_ALS_INT_ENABLE << 1) & VEML7700_ALS_INT_EN_MASK);
            break;
          
        default:
            data |= ( (VEML7700_ALS_INT_DISABLE << 1) & VEML7700_ALS_INT_EN_MASK);  
            break;
    }
    
    // Write modified parameters back to config register
    veml7700_setALSConf(data);   
}

void veml7700_setConf_ALS_SD(VEML7700_SD shutdown)
{    
    // Get config register value
    uint16_t data = veml7700_getALSConf();
    
    //Set all data in the bitmask to zero
    data &= ~(VEML7700_ALS_SD_MASK);
    
    // Bitmask with gain setting
    switch (shutdown){
        case VEML7700_POWER_ON:
            data |= ( (VEML7700_ALS_SD_POWER_ON << 0) & VEML7700_ALS_SD_MASK);
            break;

        case VEML7700_SHUTDOWN:
            data |= ( (VEML7700_ALS_SD_SHUTDOWN << 0) & VEML7700_ALS_SD_MASK);
            break;
          
        default:
            data |= ( (VEML7700_ALS_SD_SHUTDOWN << 0) & VEML7700_ALS_SD_MASK);  
            break;
    }
    
    // Write modified parameters back to config register
    veml7700_setALSConf(data);   
}

uint16_t veml7700_getALSConf() 
{
    uint8_t data[2];
    uint16_t temp;
    veml7700_read(VEML7700_ALS_CONFIG, data, 2);
    memcpy(&temp, data, 2);
    return temp;
}

void veml7700_setALSConf(uint16_t conf) 
{
    uint8_t data[2];
    data[0] =  conf  & 0xFF;
    data[1] = (conf >> 8) & 0xFF;
    veml7700_write(VEML7700_ALS_CONFIG, data, 2);
}
 
void veml7700_setALS_WH(uint16_t wh) 
{
    uint8_t data[2];
    data[0] =  wh & 0xFF ;
    data[1] = (wh >> 8) & 0xFF ;
    veml7700_write(VEML7700_ALS_THREHOLD_HIGH, data, 2);
}
 
void veml7700_setALS_WL(uint16_t wl) 
{
    uint8_t data[2];
    data[0] = wl & 0xFF;
    data[1] = (wl >> 8) & 0xFF;
    veml7700_write(VEML7700_ALS_THREHOLD_LOW, data, 2);
}
 
void veml7700_setPowerSaving(bool enable, VEML7700_POWER_SAVE powermode) 
{    
    // Read existing powersaving config into buffer
    uint8_t data[2];
    veml7700_read(VEML7700_ALS_POWER_SAVE, data, 2);
    
    // Check if power saving mode has to enabled
    data[0] &= ~(VEML7700_PSM_EN_MASK); // Clear power save enable bit
    if(enable)
    {
        // Set bits to enable power saving mode
        data[0] |= ( (VEML7700_POWERSAVE_ON << 0) & VEML7700_PSM_EN_MASK);
    }else{
        // Set bits to disable power saving mode
        data[0] |= ( (VEML7700_POWERSAVE_OFF << 0) & VEML7700_PSM_EN_MASK);
    }
    
    // Set power saving mode
    switch (powermode){
        case VEML7700_PS_MODE1:
            data[0] |= ( (VEML7700_POWERSAVE_MODE1 << 1) & VEML7700_PSM_MASK);
          break;
          
        case VEML7700_PS_MODE2:
            data[0] |= ( (VEML7700_POWERSAVE_MODE2 << 1) & VEML7700_PSM_MASK);
          break;
        
        case VEML7700_PS_MODE3:
            data[0] |= ( (VEML7700_POWERSAVE_MODE3 << 1) & VEML7700_PSM_MASK);
          break;
          
        case VEML7700_PS_MODE4:
            data[0] |= ( (VEML7700_POWERSAVE_MODE4 << 1) & VEML7700_PSM_MASK);
          break;
          
        default:
            data[0] |= ( (VEML7700_POWERSAVE_MODE1 << 1) & VEML7700_PSM_MASK);
          break;
    }

    // Write settings to register
    data[0] &= 0xFF;
    data[1] = (0x00 & 0xFF); // bit 8-16 of this register are reserved and thus not used
    veml7700_write(VEML7700_ALS_POWER_SAVE, data, 2);
}
 
uint16_t veml7700_getALS(veml7700_data * p_data)
{
    uint16_t als = 0;
    uint8_t cmd = VEML7700_ALS_DATA;
    uint8_t data[2];
    veml7700_read(cmd, data, 2);
    als = (data[1] << 8) | data[0];
    
    // Copy into buffer
    memcpy(p_data->ALS, als, 2);
    return( als );
}
 
uint16_t veml7700_getWHITE(void) 
{
    uint16_t white = 0;
    uint8_t cmd = VEML7700_WHITE_DATA;
    uint8_t data[2];
    veml7700_read(cmd, data, 2);
    white = (data[1] << 8) | data[0];
    return( white );
}
 
uint16_t veml7700_getALS_INT(void) 
{
    uint16_t als_int = 0 ;
    uint8_t cmd = VEML7700_INTERRUPTSTATUS ;
    uint8_t data[2] ;
    veml7700_read(cmd, data, 2) ;
    als_int = (data[1] << 8) | data[0] ;
    return( als_int ) ;
}

