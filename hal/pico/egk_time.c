#include "egk_time.h"
#include "pico/stdlib.h"

void egk_sleep_us(uint64_t us)
{
    if (us > 0) sleep_us(us);
}

void egk_sleep_ms(uint32_t ms)
{
    if (ms > 0) sleep_ms(ms);
}