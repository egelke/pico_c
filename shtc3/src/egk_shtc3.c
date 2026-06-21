
#include "egelke.h"

#include "egk_shtc3.h"

#include <stdlib.h>
#include <stdio.h>

#define SHTC3_CMD_SLEEP                 (0xB098)    // Enter sleep mode
#define SHTC3_CMD_WAKEUP                (0x3517)    // Wakeup mode
#define SHTC3_CMD_SOFTRESET             (0x805D)    // Soft Reset
#define SHTC3_CMD_READID                (0xEFC8)    // Read Out of ID Register

#define SHTC3_CMD_NORMAL_T_F            (0x7866)    // Read T First And Clock Stretching Disabled In Normal Mode
#define SHTC3_CMD_NORMAL_H_F            (0x58E0)    // Read H First And Clock Stretching Disabled In Normal Mode

int egk_shtc3_init(egk_sensor_t *sensor, egk_i2c_dev_t *channel, bool verify)
{
    sensor->channel = channel;
    sensor->addr = SHTC3_I2C_ADDR;
    sensor->crc = EGK_CRC8_DEFAULT;
   
    if (verify) {
        int retVal;
        uint16_t id;
        
        retVal = egk_sensor_comm(sensor, SHTC3_CMD_WAKEUP, NULL, 0, 300, NULL, 0);
        if (retVal != EGK_OK) return retVal;

        retVal = egk_sensor_comm(sensor, SHTC3_CMD_READID, NULL, 0, 300, &id, 1);
        egk_sensor_comm(sensor, SHTC3_CMD_SLEEP, NULL, 0, 0, NULL, 0);
        if (retVal != EGK_OK) return retVal;
        if (id != 0x807D) return EGK_ERROR_GENERIC;
    }

    return EGK_OK;
}

int egk_shtc3_measure(egk_sensor_t *sensor, float *temperature, float *humidity)
{
    int retVal;
    uint16_t temp_data, hum_data;

    retVal = egk_sensor_comm(sensor, SHTC3_CMD_WAKEUP, NULL, 0, 300, NULL, 0);
    if (retVal != EGK_OK) return retVal;

    retVal = egk_sensor_comm(sensor, SHTC3_CMD_NORMAL_T_F, NULL, 0, 14000, &temp_data, 1);
    egk_sensor_comm(sensor, SHTC3_CMD_SLEEP, NULL, 0, 0, NULL, 0);
    if (retVal != EGK_OK) return retVal; 

    //*temperature = -45.0f + (175.0f * ((float)temp_data / 65535.0f));
    //*humidity = 100.0f * ((float)hum_data / 65535.0f);
    *temperature = (temp_data * 175.0f) / (1 << 16) - 45;
    *humidity = (hum_data * 100.0f) / (1 << 16);
    return EGK_OK;
}

int egk_shtc3_reset(egk_sensor_t *sensor)
{
    return egk_sensor_comm(sensor, SHTC3_CMD_SOFTRESET, NULL, 0, 300, NULL, 0);
}