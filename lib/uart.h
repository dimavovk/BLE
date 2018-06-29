#include "nrf_gpio.h"
#include "nrf_uart.h"

void uartTxChar(char data);
void uartTxStr(char *str);
void uartTxBuf(uint8_t *data,uint16_t length);
void uartInit(void);
