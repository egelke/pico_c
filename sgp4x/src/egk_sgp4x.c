#include <stdio.h>
#include <stdlib.h>

#include "egelke.h"

#include "egk_time.h"
#include "egk_sgp4x.h"
#include "egk_sensor.h"

#define SGP40_CMD_FEATURE_SET                 (0x202F)    // get feature set command


int egk_sgp4x_init(egk_sensor_t *sensor, egk_i2c_dev_t *channel, uint8_t addr, bool verify) {
    sensor->channel = channel;
    sensor->addr = addr;
    sensor->crc = EGK_CRC8_DEFAULT;

    if (verify) {
        int retVal;
        uint16_t id;
        
        retVal = egk_sensor_comm(sensor, SGP40_CMD_FEATURE_SET, NULL, 0, 250, &id, 1);
        if (retVal != EGK_OK) return retVal;
        if ((id & 0xFF00) != 0x3200) return EGK_ERROR_GENERIC;
    }

    return EGK_OK;
}