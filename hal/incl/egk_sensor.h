#ifndef EGK_SENSOR_H
#define EGK_SENSOR_H

#include <stdint.h>
#include <stdbool.h>

#include "egk_i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t init;
    uint16_t poly;
    bool reflect_input;
    bool reflect_output;
    uint8_t final_xor;
} egk_crc_t;


#define EGK_CRC8_DEFAULT  (egk_crc_t){0xFF, 0x31, false, false, 0x00}


typedef struct {
    egk_i2c_dev_t *channel;
    uint8_t addr;
    egk_crc_t crc;
} egk_sensor_t;



int egk_sensor_init(egk_sensor_t *sensor, egk_i2c_dev_t *channel, uint8_t addr, egk_crc_t crc);
int egk_sensor_comm(egk_sensor_t *sensor, uint16_t command, uint16_t *req, size_t req_len, uint64_t sleep_us, uint16_t *resp, size_t resp_len);


#ifdef __cplusplus
}
#endif


#endif /* EGK_SENSOR_H */