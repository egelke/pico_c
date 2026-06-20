#ifndef SHTC3_H
#define SHTC3_H

#include <stdint.h>
#include <stdbool.h>

#include "egk_i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    egk_i2c_dev_t *channel;
    uint8_t addr;
} egk_shtc3_t;

int egk_shtc3_init(egk_shtc3_t *sensor, egk_i2c_dev_t *channel, uint8_t addr, bool verify);
int egk_shtc3_measure(egk_shtc3_t *sensor, float *temperature, float *humidity);
int egk_shtc3_reset(egk_shtc3_t *sensor);

#ifdef __cplusplus
}
#endif

#endif /* SHTC3_H */
