#include "temp.h"

#define MASK_SIGN           0x00000200UL
#define MASK_SIGN_EXTENSION 0xfffffc00UL

float nrf_temp_get(void)
{
  float temp=0;
        NRF_TEMP->TASKS_START = 1;
        while (NRF_TEMP->EVENTS_DATARDY == 0)
        {}
        NRF_TEMP->EVENTS_DATARDY = 0;
        temp = ((NRF_TEMP->TEMP & MASK_SIGN) != 0) ? (NRF_TEMP->TEMP | MASK_SIGN_EXTENSION) : (NRF_TEMP->TEMP);  
        NRF_TEMP->TASKS_STOP = 1;
   return temp/4;
}
