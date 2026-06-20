#ifndef EGK_SGP4X_H
#define EGK_SGP4X_H

#include <stdint.h>
#include <stdbool.h>

#include "egk_i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    egk_i2c_dev_t *channel;
    uint8_t addr;
} egk_sgp4x_t;

int egk_sgp4x_init(egk_sgp4x_t *sensor, egk_i2c_dev_t *channel, uint8_t addr, bool verify);
//int egk_sgp4x_measure(egk_sgp4x_t *sensor, float *temperature, float *humidity);
//int egk_sgp4x_reset(egk_sgp4x_t *sensor);

#ifdef __cplusplus
}
#endif

#endif /* EGK_SGP4X_H */
