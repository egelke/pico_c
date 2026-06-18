#ifndef SHTC3_H
#define SHTC3_H

#include <stdint.h>
#include <stdbool.h>

#include "../../hal/incl/egk_i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    egk_i2c_dev_t *channel;
    uint8_t addr;
} egk_shtc3_t;

int egk_shtc3_init(egk_shtc3_t *sensor, egk_i2c_dev_t *channel, uint8_t addr, bool verify);

#ifdef __cplusplus
}
#endif

#endif /* SHTC3_H */
