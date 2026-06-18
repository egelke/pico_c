#ifndef EGK_TIME_H
#define EGK_TIME_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void egk_sleep_us(uint64_t us);
void egk_sleep_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* EGK_TIME_H */