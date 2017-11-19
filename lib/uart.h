#include "nrf_gpio.h"
#include "nrf_uart.h"

void uartTxChar(uint8_t data);
void uartTxStr(uint8_t *str);
void uartTxBuf(uint8_t *data,uint16_t length);
void uartInit(void);
