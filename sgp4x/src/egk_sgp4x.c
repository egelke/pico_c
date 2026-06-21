#include <stdio.h>
#include <stdlib.h>

#include "egelke.h"

#include "egk_time.h"
#include "egk_sgp4x.h"
#include "egk_sensor.h"

//#define SGP40_CMD_FEATURE_SET                 (0x202F)    // get feature set command
#define SGP40_CMD_SELF_TEST                   (0x280E)    // measure test command
#define SGP40_CMD_MEASURE_RAW                 (0x260F)    // measure raw command

int egk_sgp4x_init(egk_sensor_t *sensor, egk_i2c_dev_t *channel, bool verify) {
    sensor->channel = channel;
    sensor->addr = SGP40_I2C_ADDR;
    sensor->crc = EGK_CRC8_DEFAULT;

    if (verify) {
        int retVal;
        uint16_t result;
        
        retVal = egk_sensor_comm(sensor, SGP40_CMD_SELF_TEST, NULL, 0, 320*1000, &result, 1);
        if (retVal != EGK_OK) return retVal;
        if ((result & 0xFF00) != 0xD400) return EGK_ERROR_GENERIC;
    }

    return EGK_OK;
}