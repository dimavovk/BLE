#include "gpio.h"

void gpio_init(void)
{
	nrf_gpio_cfg_output(PIN_LED0);
  nrf_gpio_cfg_output(PIN_LED1);
  nrf_gpio_cfg_output(PIN_LED2);
  nrf_gpio_cfg_output(PIN_LED3);
  nrf_gpio_cfg_output(PIN_LED4);
}
