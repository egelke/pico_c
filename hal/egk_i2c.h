#ifndef EGK_I2C_H
#define EGK_I2C_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    I2C_MODE_NORMAL =       100000,
    I2C_MODE_FAST =         400000,
    I2C_MODE_FAST_PLUS =    1000000
} egk_i2c_mode_t;

typedef struct egk_i2c_dev egk_i2c_dev_t;


int egk_i2c_init(egk_i2c_dev_t *dev, egk_i2c_mode_t baudrate, int sda_pin, int scl_pin);

int egk_i2c_write(egk_i2c_dev_t *dev, uint8_t addr, uint8_t *data, size_t len);

int egk_i2c_read(egk_i2c_dev_t *dev, uint8_t addr, uint8_t *data, size_t len);

void egk_i2c_free(egk_i2c_dev_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* EGK_I2C_H */