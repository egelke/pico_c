
#include "../main.h"
#include "../hal/egk_time.h"

#include "egk_shtc3.h"

#include <stdlib.h>

#define SHTC3_REG_SLEEP                 (0xB098)    // Enter sleep mode
#define SHTC3_REG_WAKEUP                (0x3517)    // Wakeup mode
#define SHTC3_REG_SOFTRESET             (0x805D)    // Soft Reset
#define SHTC3_REG_READID                (0xEFC8)    // Read Out of ID Register

uint8_t egk_shtc3_crc8(uint8_t *data, uint16_t len)
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

int egk_shtc3_write(egk_shtc3_t *sensor, uint16_t word)
{
    int retVal;
    uint8_t buffer[2];
    buffer[0] = word >> 8;
    buffer[1] = word & 0xff;
    return egk_i2c_write(sensor->channel, sensor->addr, buffer, 2);
}

int egk_shtc3_read(egk_shtc3_t *sensor, uint16_t *word) 
{
    int retVal;
    uint8_t csc;
    uint8_t buffer[3] = {0x00, 0x00,  0xAC};
    //csc = egk_shtc3_crc8(buffer, 2);
    //if (csc != buffer[2]) return EGK_ERROR_CRC;

    retVal = egk_i2c_read(sensor->channel, sensor->addr, buffer, 3);
    if (retVal != EGK_OK) return retVal;

    
    csc = egk_shtc3_crc8(buffer, 2);
    if (csc != buffer[2]) return EGK_ERROR_CRC;

    *word = (buffer[0] << 8) + buffer[1];

    return EGK_OK;
}

int egk_shtc3_wakeup(egk_shtc3_t *sensor)
{
    int retVal;
    retVal = egk_shtc3_write(sensor, SHTC3_REG_WAKEUP);
    egk_sleep_us(300);
    return retVal;
}

int egk_shtc3_sleep(egk_shtc3_t *sensor)
{
    int retVal;
    retVal = egk_shtc3_write(sensor, SHTC3_REG_SLEEP);
    egk_sleep_us(300);
    return retVal;
}

int egk_shtc3_comm(egk_shtc3_t *sensor, uint16_t command, uint16_t *response)
{
    int retVal;

    retVal = egk_shtc3_wakeup(sensor);
    if (retVal != EGK_OK) return retVal;
    egk_sleep_us(300);

    retVal = egk_shtc3_write(sensor, command);
    if (retVal != EGK_OK) return retVal;
    egk_sleep_ms(14);

    retVal = egk_shtc3_read(sensor, response);

    egk_shtc3_sleep(sensor);
    //egk_sleep_us(300);

    return retVal;
}

int egk_shtc3_init(egk_shtc3_t *sensor, egk_i2c_dev_t *channel, uint8_t addr, bool verify)
{
    sensor->channel = channel;
    sensor->addr = addr;
   
    if (verify) {
        int retVal;
        uint16_t id;
        
        retVal = egk_shtc3_comm(sensor, SHTC3_REG_READID, &id);
        if (retVal != EGK_OK) return retVal;
        if (id != 0x807D) return EGK_ERROR_GENERIC;
    }

    return EGK_OK;
}

