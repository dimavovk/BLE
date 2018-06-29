#include "uart.h"

#define UART_RX_PIN 11
#define UART_TX_PIN 9

uint8_t uart_data=0;

void UART0_IRQHandler(void)
{
        if (nrf_uart_int_enable_check(NRF_UART0, NRF_UART_INT_MASK_RXDRDY) &&
                nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_RXDRDY))
        
        {
             nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXDRDY);
             uart_data = nrf_uart_rxd_get(NRF_UART0);
             uartTxChar(uart_data);
           
        }

}
void uartTxChar(char data)
{
    nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STARTTX);
    nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_TXDRDY);
    nrf_uart_txd_set(NRF_UART0,(uint8_t)data);
    while(!nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_TXDRDY)){}
    nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STOPTX);
}  
void uartTxBuf(uint8_t *data,uint16_t length)
{
  uint16_t cnt=0;
  for(cnt=0;cnt<length;cnt++)
  {
    uartTxChar(*(data+cnt));
  }
}  
void uartTxStr(char *str)
{
  while(*str!=0)
  {
    uartTxChar(*str++);
  }
} 
void uartInit(void)
{
  nrf_gpio_cfg_output(UART_TX_PIN);
  nrf_gpio_cfg_input(UART_RX_PIN,NRF_GPIO_PIN_NOPULL);
 
  nrf_uart_baudrate_set(NRF_UART0,NRF_UART_BAUDRATE_9600);
  nrf_uart_configure(NRF_UART0,NRF_UART_PARITY_EXCLUDED,NRF_UART_HWFC_DISABLED);
  nrf_uart_txrx_pins_set(NRF_UART0,UART_TX_PIN,UART_RX_PIN);
  nrf_uart_enable(NRF_UART0);
 
 /* nrf_uart_int_enable(NRF_UART0, NRF_UART_INT_MASK_RXDRDY | NRF_UART_INT_MASK_ERROR);

  NVIC_ClearPendingIRQ(UART0_IRQn);
  NVIC_SetPriority(UART0_IRQn, 0);
  NVIC_EnableIRQ(UART0_IRQn);*/
  
 // nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STARTTX);
  nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STARTRX);
}
