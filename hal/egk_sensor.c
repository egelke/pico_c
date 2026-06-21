#include "egelke.h"
#include "egk_sensor.h"
#include "egk_time.h"

#include <stdlib.h>

uint8_t egk_sensor_crc8(egk_sensor_t *sensor, uint8_t *data, uint16_t len)
{
    uint8_t crc = sensor->crc.init;
    while (len--)
    {
        crc ^= *data;
        
        for (uint8_t i = 0; i < 8; i++)
        {
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ sensor->crc.poly;
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

int egk_sensor_init(egk_sensor_t *sensor, egk_i2c_dev_t *channel, uint8_t addr, egk_crc_t crc) 
{
    sensor->channel = channel;
    sensor->addr = addr;
    sensor->crc = crc;

    return EGK_OK;
}

int egk_sensor_write(egk_sensor_t *sensor, uint16_t command, uint16_t *req, size_t req_len) {
    size_t buffer_len = 2 + (req_len * 3); // command + req + crc
    uint8_t *buffer = malloc(buffer_len);
    if (!buffer) return EGK_ERROR_GENERIC;
    
    buffer[0] = command >> 8;
    buffer[1] = command & 0xff;
    for (size_t i = 0; i < req_len; i++) {
        buffer[2 + (i * 3)] = req[i] >> 8;
        buffer[2 + (i * 3) + 1] = req[i] & 0xff;
        buffer[2 + (i * 3) + 2] = egk_sensor_crc8(sensor, &buffer[2 + (i * 3)], 2);
    }

    int retVal = egk_i2c_write(sensor->channel, sensor->addr, buffer, buffer_len, false);
    free(buffer);
    return retVal;
}

int egk_sensor_read(egk_sensor_t *sensor, uint16_t *resp, size_t resp_len) {
    if (resp_len == 0) return EGK_OK;

    uint8_t *buffer = calloc(resp_len, 3); // allocate space for response and CRC
    if (!buffer) return EGK_ERROR_GENERIC;

    int retVal = egk_i2c_read(sensor->channel, sensor->addr, buffer, resp_len * 3, false);
    if (retVal != EGK_OK) {
        free(buffer);
        return retVal;
    }

    for (size_t i = 0; i < resp_len; i++) {
        if (egk_sensor_crc8(sensor, &buffer[i * 3], 2) != buffer[(i * 3) + 2]) {
            free(buffer);
            return EGK_ERROR_CRC;
        }
        resp[i] = (buffer[i * 3] << 8) + buffer[(i * 3) + 1];
    }

    free(buffer);
    return EGK_OK;
}

int egk_sensor_comm(egk_sensor_t *sensor, uint16_t command, uint16_t *req, size_t req_len, uint64_t sleep_us, uint16_t *resp, size_t resp_len) {
    int retVal;

    retVal = egk_sensor_write(sensor, command, req, req_len);
    if (retVal != EGK_OK) return retVal;
    

    egk_sleep_us(sleep_us);

    retVal = egk_sensor_read(sensor, resp, resp_len);
    if (retVal != EGK_OK) return retVal;
    
    return EGK_OK;
}