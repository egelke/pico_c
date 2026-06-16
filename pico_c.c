#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_MODE_NORMAL                 (100*1000)
#define I2C_MODE_FAST                   (400*1000)
#define I2C_MODE_FAST_PLUS              (1000*1000)

#define SENSOR_I2C_PORT                 (i2c0)
#define SENSOR_SDA_PIN                  (8)
#define SENSOR_SCL_PIN                  (9)
#define SHTC3_I2C_ADDR                  (0X70)

#define SHTC3_REG_SLEEP                 (0xB098)    // Enter sleep mode
#define SHTC3_REG_WAKEUP                (0x3517)    // Wakeup mode
#define SHTC3_REG_SOFTRESET             (0x805D)    // Soft Reset
#define SHTC3_REG_READID                (0xEFC8)    // Read Out of ID Register

#define SHTC3_ERROR_IO                  (-2)
#define SHTC3_ERROR_CRC                 (-3)

uint8_t shtc3_crc8(uint8_t *data, uint16_t len)
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


int shtc3_write(i2c_inst_t * i2c, uint8_t addr, uint16_t word)
{
    int retVal;
    uint8_t buffer[2];
    buffer[0] = word >> 8;
    buffer[1] = word & 0xff;
    retVal = i2c_write_blocking(i2c, addr, buffer, 2, false);
    if (retVal == PICO_ERROR_GENERIC) return retVal;
    if (retVal != 2) return SHTC3_ERROR_IO;
}

int shtc3_read(i2c_inst_t * i2c, uint8_t addr, uint16_t *word) 
{
    int retVal;
    uint8_t csc;
    uint8_t buffer[3];

    retVal = i2c_read_blocking(SENSOR_I2C_PORT, SHTC3_I2C_ADDR, buffer, 3, false);
    if (retVal == PICO_ERROR_GENERIC) return retVal;
    if (retVal != 3) return SHTC3_ERROR_IO;

    csc = shtc3_crc8(buffer, 2);
    if (csc != buffer[2]) return SHTC3_ERROR_CRC;
    return ERROR_SUCCESS;
}

int shtc3_wakeup(i2c_inst_t * i2c, uint8_t addr) 
{
    return shtc3_write(i2c, addr, SHTC3_REG_WAKEUP);
}

int main()
{
    stdio_init_all();

    i2c_init(SENSOR_I2C_PORT, I2C_MODE_NORMAL);
        
    gpio_set_function(SENSOR_SDA_PIN,GPIO_FUNC_I2C);
    gpio_set_function(SENSOR_SCL_PIN,GPIO_FUNC_I2C);
    gpio_pull_up(SENSOR_SDA_PIN);
    gpio_pull_up(SENSOR_SCL_PIN);
    

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
