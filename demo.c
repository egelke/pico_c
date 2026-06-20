#include <stdio.h>
#include <stdlib.h>

#include "demo.h"
#include "pico/stdlib.h"
#include "egk_i2c_pico.h"
#include "egk_time.h"
#include "egk_shtc3.h"

#define SENSOR_I2C_PORT                 (i2c0)
#define SENSOR_SDA_PIN                  (8)
#define SENSOR_SCL_PIN                  (9)
#define SHTC3_I2C_ADDR                  (0X70)

egk_i2c_dev_t *i2c_dev = NULL;

void cleanup()
{
    egk_i2c_free(i2c_dev); //no need for null check, egk_i2c_free is safe to call with null
}

int error(const char *msg, int code)
{
    printf("%s: %X\n", msg, code);
    cleanup(); //it's a microcontroller, so cleanup is not strictly necessary, but it's good practice to free resources when possible
    return -1;
}


int main()
{
    int retVal;
    egk_shtc3_t sensor;
    
    stdio_init_all();
    printf("PICO Sensor Kit\n");

    i2c_dev = egk_i2c_pico_new(SENSOR_I2C_PORT);
    if (!i2c_dev) return error("Failed to initialize I2C", -1);

    retVal = egk_i2c_init(i2c_dev, I2C_MODE_NORMAL, SENSOR_SDA_PIN, SENSOR_SCL_PIN);
    if (retVal != EGK_OK) return error("Failed to initialize I2C", retVal);

    retVal = egk_shtc3_init(&sensor, i2c_dev, SHTC3_I2C_ADDR, true);
    if (retVal != EGK_OK) return error("Failed to initialize SHTC3 sensor", retVal);

    //retVal = egk_shtc3_reset(&sensor);
    //if (retVal != EGK_OK) return error("Failed to reset SHTC3 sensor", retVal);

    while (true)
    {
        float temperature, humidity;
        retVal = egk_shtc3_measure(&sensor, &temperature, &humidity);
        if (retVal != EGK_OK) return error("Failed to measure SHTC3 sensor", retVal);
        printf("Temperature: %.2f C, Humidity: %.2f %%\n", temperature, humidity);

        egk_sleep_ms(1000);
    }
    
    cleanup(); //for good measure, we should never reach this point, but if we do, cleanup and exit
}
