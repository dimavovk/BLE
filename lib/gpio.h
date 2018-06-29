#include "nrf_gpio.h"

#define PIN_LED4 22
#define PIN_LED3 21
#define PIN_LED2 20
#define PIN_LED1 19
#define PIN_LED0 18

#define SET_GPIO(pin) 			nrf_gpio_pin_write(pin,1);
#define RESET_GPIO(pin) 		nrf_gpio_pin_write(pin,0);

void gpio_init(void);
