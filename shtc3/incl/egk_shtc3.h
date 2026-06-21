#ifndef SHTC3_H
#define SHTC3_H

#include <stdint.h>
#include <stdbool.h>

#include "egk_sensor.h"

#define SHTC3_I2C_ADDR                  (0X70)

#ifdef __cplusplus
extern "C" {
#endif


int egk_shtc3_init(egk_sensor_t *sensor, egk_i2c_dev_t *channel, bool verify);
int egk_shtc3_measure(egk_sensor_t *sensor, float *temperature, float *humidity);
int egk_shtc3_reset(egk_sensor_t *sensor);

#ifdef __cplusplus
}
#endif

#endif /* SHTC3_H */
