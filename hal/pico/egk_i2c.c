
#include "../../incl/error.h"

#include "egk_i2c_pico.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <stdlib.h>

struct egk_i2c_dev {
    i2c_inst_t *i2c;
};

egk_i2c_dev_t * egk_i2c_pico_new(i2c_inst_t *i2c)
{
    egk_i2c_dev_t *dev = malloc(sizeof(egk_i2c_dev_t));
    dev->i2c = i2c;

    return dev;
}

int egk_i2c_init(egk_i2c_dev_t *dev, egk_i2c_mode_t baudrate, int sda_pin, int scl_pin)
{
    int retVal;
    retVal = i2c_init(dev->i2c, baudrate);
    if (retVal != baudrate) return EGK_ERROR_IO;
        
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);

    return EGK_OK;
}

int egk_i2c_write(egk_i2c_dev_t *dev, uint8_t addr, uint8_t *data, size_t len)
{
    int retVal;
    retVal = i2c_write_blocking(dev->i2c, addr, data, len, false);
    if (retVal == PICO_ERROR_GENERIC) return EGK_ERROR_GENERIC;
    if (retVal != len) return EGK_ERROR_IO;

    return EGK_OK;
}

int egk_i2c_read(egk_i2c_dev_t *dev, uint8_t addr, uint8_t *data, size_t len)
{
    int retVal;
    retVal = i2c_read_blocking(dev->i2c, addr, data, len, false);
    if (retVal == PICO_ERROR_GENERIC) return EGK_ERROR_GENERIC;
    if (retVal != len) return EGK_ERROR_IO;

    return EGK_OK;
}

void egk_i2c_free(egk_i2c_dev_t *dev)
{
    if (dev) free(dev);
}