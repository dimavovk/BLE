#include "nrf_gpio.h"
#include "uart.h" 
#include "nrf.h"
#include "softdevice_handler.h"
#include "string.h"
#include "app_error.h"
#include "ble_advdata.h"
#include "ble_srv_common.h"

#include "nrf_soc.h"
#include "gpio.h"




#define IS_SRVC_CHANGED_CHARACT_PRESENT  1 
#define APP_ADV_INTERVAL                 300                                        /**< The advertising interval (in units of 0.625 ms. This value corresponds to 25 ms). */
#define APP_ADV_TIMEOUT_IN_SECONDS       180  


#define MIN_CONN_INTERVAL                MSEC_TO_UNITS(100, UNIT_1_25_MS)           /**< Minimum acceptable connection interval (0.1 seconds). */
#define MAX_CONN_INTERVAL                MSEC_TO_UNITS(200, UNIT_1_25_MS)           /**< Maximum acceptable connection interval (0.2 second). */
#define SLAVE_LATENCY                    0                                          /**< Slave latency. */
#define CONN_SUP_TIMEOUT                 MSEC_TO_UNITS(4000, UNIT_10_MS)            /**< Connection supervisory timeout (4 seconds). */


#define DEVICE_NAME                      "Hello"  



static void on_ble_evt(ble_evt_t * p_ble_evt);
static void advertising_init(void);
static void ble_evt_dispatch(ble_evt_t * p_ble_evt);
static void sys_evt_dispatch(uint32_t sys_evt);
static void ble_stack_init(void);
static void gap_params_init(void);
static void advertising_init(void);

/**@brief Function for dispatching a BLE stack event to all modules with a BLE stack event handler.
 *
 * @details This function is called from the BLE Stack event interrupt handler after a BLE stack
 *          event has been received.
 *
 * @param[in] p_ble_evt  Bluetooth stack event.
 */
 
/**@brief Function for handling the Application's BLE Stack events.
 *
 * @param[in] p_ble_evt  Bluetooth stack event.
 */
static void on_ble_evt(ble_evt_t * p_ble_evt)
{


    switch (p_ble_evt->header.evt_id)
            {
        case BLE_GAP_EVT_CONNECTED:
							uartTxStr("on_ble_evt\n");
            break;

        case BLE_GAP_EVT_DISCONNECTED:
							uartTxStr("on_ble_evt\n");
            break;

        default:
            // No implementation needed.
            break;
    }
}

static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
   // dm_ble_evt_handler(p_ble_evt);
   // ble_conn_params_on_ble_evt(p_ble_evt);
   // bsp_btn_ble_on_ble_evt(p_ble_evt);
    on_ble_evt(p_ble_evt);
   // ble_advertising_on_ble_evt(p_ble_evt);
}
/**@brief Function for dispatching a system event to interested modules.
 *
 * @details This function is called from the System event interrupt handler after a system
 *          event has been received.
 *
 * @param[in] sys_evt  System stack event.
 */
static void sys_evt_dispatch(uint32_t sys_evt)
{
		uartTxStr("sys_evt_dispatch\n");
}

static void ble_stack_init(void)
{
	  uint32_t err_code;
		ble_enable_params_t ble_enable_params;
	
		/*Enables the SoftDevice and by extension the protocol stack*/
		SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM,NULL);
	
		memset(&ble_enable_params,0,sizeof(ble_enable_params));
		ble_enable_params.gatts_enable_params.service_changed =  IS_SRVC_CHANGED_CHARACT_PRESENT;
		ble_enable_params.gatts_enable_params.attr_tab_size   =   BLE_GATTS_ATTR_TAB_SIZE_DEFAULT;
		sd_ble_enable(&ble_enable_params);
	
    // Register with the SoftDevice handler module for BLE events.
    err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
		APP_ERROR_CHECK(err_code);
    // Register with the SoftDevice handler module for BLE events.
    err_code = softdevice_sys_evt_handler_set(sys_evt_dispatch);
	  APP_ERROR_CHECK(err_code);

}
static void gap_params_init(void)
{
	  uint32_t                err_code;
    ble_gap_conn_params_t   gap_conn_params;
    ble_gap_conn_sec_mode_t sec_mode;
	
	  BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);
	
	  err_code = sd_ble_gap_device_name_set(&sec_mode,(const uint8_t *)DEVICE_NAME,strlen(DEVICE_NAME));
	  APP_ERROR_CHECK(err_code);
	
    memset(&gap_conn_params, 0, sizeof(gap_conn_params));

    gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
    gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
    gap_conn_params.slave_latency     = SLAVE_LATENCY;
    gap_conn_params.conn_sup_timeout  = CONN_SUP_TIMEOUT;

    err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
	  APP_ERROR_CHECK(err_code);

}

static void advertising_init(void)
{ 
    uint32_t      err_code;

    ble_advdata_t advdata;
    ble_gap_adv_params_t adv_params;

	  // Build advertising data struct to pass into @ref ble_advertising_init.
    memset(&advdata, 0, sizeof(advdata));
	
    ble_uuid_t m_adv_uuids[] = {{BLE_UUID_DEVICE_INFORMATION_SERVICE, BLE_UUID_TYPE_BLE}};
		


    advdata.name_type               = BLE_ADVDATA_FULL_NAME;
    advdata.include_appearance      = true;
    advdata.flags                   = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    advdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
    advdata.uuids_complete.p_uuids  = m_adv_uuids;
		

    err_code = ble_advdata_set(&advdata,NULL);
    APP_ERROR_CHECK(err_code);
 
		
    memset(&adv_params, 0, sizeof(adv_params));
    adv_params.type        = BLE_GAP_ADV_TYPE_ADV_IND;
    adv_params.fp          = BLE_GAP_ADV_FP_ANY;
    adv_params.interval=APP_ADV_INTERVAL;
    adv_params.timeout=0;


    err_code = sd_ble_gap_adv_start(&adv_params);
		APP_ERROR_CHECK(err_code);
}


int main(void)
{
	gpio_init();
  SET_GPIO(PIN_LED2);
  uartInit();
  ble_stack_init();
	gap_params_init();
  advertising_init();
	//sd_ble_gap_conn_param_update(m_conn_handle, &gap_conn_params);
	
	uartTxStr("Start programm...\n");
  while(1)
  {  
   
	
  }

}

