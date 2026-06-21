#ifndef EGK_SGP4X_H
#define EGK_SGP4X_H

#include <stdint.h>
#include <stdbool.h>

#include "egk_sensor.h"

#define SGP40_I2C_ADDR                  (0x59)

#ifdef __cplusplus
extern "C" {
#endif


int egk_sgp4x_init(egk_sensor_t *sensor, egk_i2c_dev_t *channel, bool verify);
//int egk_sgp4x_measure(egk_sgp4x_t *sensor, float *temperature, float *humidity);
//int egk_sgp4x_reset(egk_sgp4x_t *sensor);

#ifdef __cplusplus
}
#endif

#endif /* EGK_SGP4X_H */
