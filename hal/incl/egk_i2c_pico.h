#ifndef EGK_I2C_PICO_H
#define EGK_I2C_PICO_H

#include "egk_i2c.h"
#include "hardware/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

egk_i2c_dev_t* egk_i2c_pico_new(i2c_inst_t *i2c);

#ifdef __cplusplus
}
#endif

#endif /* EGK_I2C_PICO_H */