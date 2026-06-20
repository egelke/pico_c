#include <stdio.h>
#include <stdlib.h>

#include "egelke.h"

#include "egk_time.h"
#include "egk_sgp4x.h"

#define SGP40_CMD_FEATURE_SET                 (0x202F)    // get feature set command

uint8_t egk_sgp4x_crc8(uint8_t *data, uint16_t len)
{
    uint8_t crc = 0xff;
    uint8_t poly = 0x31;
    while (len--)
    {
        crc ^= *data;
        
        for (uint8_t i = 0; i < 8; i++)
        {
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ poly;
            }
            else
            {
                crc = crc << 1;
            }

        }
        data++;
    }
    return crc;
}

int egk_sgp4x_write(egk_sgp4x_t *sensor, uint16_t word)
{
    int retVal;
    uint8_t buffer[2];
    buffer[0] = word >> 8;
    buffer[1] = word & 0xff;
    return egk_i2c_write(sensor->channel, sensor->addr, buffer, 2);
}

int egk_sgp4x_read(egk_sgp4x_t *sensor, uint16_t *word) 
{
    int retVal;
    uint8_t csc;
    uint8_t buffer[3];

    retVal = egk_i2c_read(sensor->channel, sensor->addr, buffer, 3);
    if (retVal != EGK_OK) return retVal;

    if (egk_sgp4x_crc8(buffer, 2) != buffer[2]) return EGK_ERROR_CRC;
    *word = (buffer[0] << 8) + buffer[1];

    return EGK_OK;
}

int egk_sgp4x_comm(egk_sgp4x_t *sensor, uint16_t command, uint16_t *resp)
{
    int retVal;

    retVal = egk_sgp4x_write(sensor, command);
    if (retVal != EGK_OK) return retVal;
    egk_sleep_us(250);

    retVal = egk_sgp4x_read(sensor, resp);
    if (retVal != EGK_OK) return retVal;

    return retVal;
}

int egk_sgp4x_init(egk_sgp4x_t *sensor, egk_i2c_dev_t *channel, uint8_t addr, bool verify) {
    sensor->channel = channel;
    sensor->addr = addr;
   
    if (verify) {
        int retVal;
        uint16_t id;
        
        retVal = egk_sgp4x_comm(sensor, SGP40_CMD_FEATURE_SET, &id);
        if (retVal != EGK_OK) return retVal;
        if (id != 0x3220) return EGK_ERROR_GENERIC;
    }

    return EGK_OK;
}