#include "nrf_gpio.h"
#include "uart.h" 
#include "nrf.h"
#include "softdevice_handler.h"
#include "string.h"
#include "app_error.h"
#include "ble_advdata.h"
#include "ble_srv_common.h"

#include "nrf_soc.h"

#define PIN_LED4 22
#define PIN_LED3 21
#define PIN_LED2 20
#define PIN_LED1 19
#define PIN_LED0 18


#define IS_SRVC_CHANGED_CHARACT_PRESENT  1 
#define APP_ADV_INTERVAL                 300                                        /**< The advertising interval (in units of 0.625 ms. This value corresponds to 25 ms). */
#define APP_ADV_TIMEOUT_IN_SECONDS       180  


#define DEVICE_NAME                      "Hello world"  

uint32_t error=0;


static void advertising_init(void);

/*
void SWI0_IRQHandler(void)
{
  //uint8_t mp_ble_evt_buffer;
 // uint16_t evt_len=sizeof(mp_ble_evt_buffer);
  nrf_gpio_pin_write(PIN_LED0,2);

}*/                                   
static void advertising_init(void)
{

  
    
    
    uint32_t      err_code;
    ble_advdata_t advdata;
    ble_gap_adv_params_t adv_params;
  
    ble_gap_conn_sec_mode_t sec_mode;

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);
    sd_ble_gap_device_name_set(&sec_mode,(const uint8_t *)DEVICE_NAME,strlen(DEVICE_NAME));
    ble_uuid_t m_adv_uuids[] = {{BLE_UUID_DEVICE_INFORMATION_SERVICE, BLE_UUID_TYPE_BLE}};
    // Build advertising data struct to pass into @ref ble_advertising_init.
    memset(&advdata, 0, sizeof(advdata));

    advdata.name_type               = BLE_ADVDATA_FULL_NAME;
    advdata.include_appearance      = true;
    advdata.flags                   = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    advdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
    advdata.uuids_complete.p_uuids  = m_adv_uuids;
  
    ble_advdata_set(&advdata,NULL);
  
    
    
    memset(&adv_params, 0, sizeof(adv_params));
    adv_params.type=BLE_GAP_ADV_TYPE_ADV_IND;
    adv_params.fp=BLE_GAP_ADV_FP_ANY;
    adv_params.interval=APP_ADV_INTERVAL;
    adv_params.timeout=0;

    sd_ble_gap_adv_start(&adv_params);
    


}

int main(void)
{
  nrf_gpio_cfg_output(PIN_LED0);
  nrf_gpio_cfg_output(PIN_LED1);
  nrf_gpio_cfg_output(PIN_LED2);
  nrf_gpio_cfg_output(PIN_LED3);
  nrf_gpio_cfg_output(PIN_LED4);
  
  nrf_gpio_pin_write(PIN_LED0,1);
  
  
  sd_softdevice_enable(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM,NULL);
  
  ble_enable_params_t ble_enable_params;
  memset(&ble_enable_params,0,sizeof(ble_enable_params));
  ble_enable_params.gatts_enable_params.service_changed =  IS_SRVC_CHANGED_CHARACT_PRESENT;
  ble_enable_params.gatts_enable_params.attr_tab_size   =   BLE_GATTS_ATTR_TAB_SIZE_DEFAULT;
  sd_ble_enable(&ble_enable_params);
  
  advertising_init();
  uartInit();
  while(1)
  {  

   // uartTxStr("Hellow\n");

  
  }

}

