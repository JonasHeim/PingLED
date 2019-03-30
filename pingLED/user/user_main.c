/*
 * ESPRSSIF MIT License
 *
 * Copyright (c) 2015 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR  OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "esp_common.h"
#include "gpio.h"
#include "i2c_master.h"
#include "TM1637.h"
#include "TM1637.h"

#define GPIO_RESET_BTN 5 	/* GPIO for external reset button */
#define WAIT_MS_DISPLAY_TEST	( 200U )	//Waiting time in ms for display test routine

/* WI-FI configuration */
#define ACCESS_POINT_SSID		( "pingLED")
#define ACCESS_POINT_PASSKEY	( "password")

/******************************************************************************
 * FunctionName : wifi_handle_event_cb
 * Description  : entry of user application, init user function here
 * Parameters   : System_Event_t*	Event that caused the callback
 * Returns      : none
*******************************************************************************/
void wifi_handle_event_cb(System_Event_t* event)
{
	switch(event->event_id)
	{
		case EVENT_SOFTAPMODE_STACONNECTED:
			printf("Client with MAC %X:%X:%X:%X:%X:%X connected.\r\n",
				event->event_info.sta_connected.mac[0],	event->event_info.sta_connected.mac[1],
				event->event_info.sta_connected.mac[2], event->event_info.sta_connected.mac[3],
				event->event_info.sta_connected.mac[4], event->event_info.sta_connected.mac[5]);
			break;
		case EVENT_SOFTAPMODE_STADISCONNECTED:
			printf("Client with MAC %X:%X:%X:%X:%X:%X disconnected\r\n",
			event->event_info.sta_disconnected.mac[0],	event->event_info.sta_disconnected.mac[1],
			event->event_info.sta_disconnected.mac[2], event->event_info.sta_disconnected.mac[3],
			event->event_info.sta_disconnected.mac[4], event->event_info.sta_disconnected.mac[5]);
			break;
		default:
			break;
	}
}

/******************************************************************************
 * FunctionName : user_rf_cal_sector_set
 * Description  : SDK just reversed 4 sectors, used for rf init data and paramters.
 *                We add this function to force users to set rf cal sector, since
 *                we don't know which sector is free in user's application.
 *                sector map for last several sectors : ABCCC
 *                A : rf cal
 *                B : rf init data
 *                C : sdk parameters
 * Parameters   : none
 * Returns      : rf cal sector
*******************************************************************************/
uint32 user_rf_cal_sector_set(void)
{
    flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        case FLASH_SIZE_64M_MAP_1024_1024:
            rf_cal_sec = 2048 - 5;
            break;

        case FLASH_SIZE_128M_MAP_1024_1024:
            rf_cal_sec = 4096 - 5;
            break;

        default:
            rf_cal_sec = 0;
            break;
    }

    return rf_cal_sec;
}

/******************************************************************************
 * FunctionName : task_display
 * Description  : RTOS task that handles the I2C 7-Segment display
 * Parameters   : void* Task Parameters
 * Returns      : none
*******************************************************************************/
void task_display(void *pvParameters) 
{ 
	printf("I2C_Task: Init I2C...\r\n"); 
	i2c_master_gpio_init();
	tm1637_init();
	tm1637_set_brightness(0x50);
	uint8_t i = 0;
	while (1) { 
		/* run display test pattern */
		for(i = 0; i < 4; i++)
		{

			tm1637_display_char(tm1637_map_char('0'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('1'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('2'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('3'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('4'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('5'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('6'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('7'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('8'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('9'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('A'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('B'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('C'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('D'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('E'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_display_char(tm1637_map_char('F'), i);
			vTaskDelay(WAIT_MS_DISPLAY_TEST / portTICK_RATE_MS);

			tm1637_clear();
		}
	} 
	vTaskDelete(NULL); 
}

typedef enum {
	RESET_STATE_IDLE = 0,
	RESET_STATE_LOW,
	RESET_STATE_TRIGGERED
} RESET_STATE_t;

/******************************************************************************
 * FunctionName : task_reset
 * Description  : RTOS task that monitors the RESET button and triggers a reset
 * Parameters   : void* Task Parameters
 * Returns      : none
*******************************************************************************/
void task_reset(void *pvParameters) 
{ 
	
	uint8_t reset_state = RESET_STATE_IDLE;
	uint8_t btn_current_level = 1;
	uint8_t reset_btn_counter = 0;

	/* set GPIO as input */
	GPIO_AS_INPUT(GPIO_RESET_BTN); 

	printf("Reset Task begin\r\n"); 

	while (1) { 
		/* sample every 50ms */
		vTaskDelay(50 / portTICK_RATE_MS);

		/* sample button level */
		btn_current_level = GPIO_INPUT_GET(GPIO_RESET_BTN);

		switch (reset_state)
		{
			case RESET_STATE_IDLE:
				
				if(0 == btn_current_level)
				{
					/* reset counter value */
					reset_btn_counter = 0;

					/* transition to next state
					* if button level is low = button is pressed
					*/
					reset_state = RESET_STATE_LOW;
				}
				break;
			case RESET_STATE_LOW:
				
				if(0 == btn_current_level)
				{
					/* if button still pressed increment counter value */
					reset_btn_counter++;

					/* button pressed long enough?
					 * 5s at samples every 50ms -> counter value greater than 100
					 */
					if(reset_btn_counter >= 100)
					{
						/* transition to next state */
						reset_state = RESET_STATE_TRIGGERED;
					}
				}
				else
				{
					/* transition to previous state
					 * button not pressed anymore
					 */
					reset_state = RESET_STATE_IDLE;
				}

				break;
			case RESET_STATE_TRIGGERED:
				printf("Reset was triggered...\r\n");
				vTaskDelay(5000 / portTICK_RATE_MS);	/* wait 5s */
				
				/* reset */
				system_restart();
				reset_state = RESET_STATE_IDLE;
				break;
			default:
				/* should not be reachable */
				reset_state = RESET_STATE_IDLE;
				break;			
		}

	} 
	vTaskDelete(NULL); 
}

/******************************************************************************
 * FunctionName : task_wireless
 * Description  : RTOS task for WIFI initialization and management
 * Parameters   : void* Task Parameters
 * Returns      : none
*******************************************************************************/
void task_wireless(void *pvParameters)
{	

    uint8 ssid[32];         /**< SSID of ESP8266 soft-AP */
    uint8 password[64];     /**< Password of ESP8266 soft-AP */
    uint8 ssid_len;         /**< Length of SSID. If softap_config.ssid_len==0, check the SSID until there is a termination character; otherwise, set the SSID length according to softap_config.ssid_len. */
    uint8 channel;          /**< Channel of ESP8266 soft-AP */
    AUTH_MODE authmode;     /**< Auth mode of ESP8266 soft-AP. Do not support AUTH_WEP in soft-AP mode */
    uint8 ssid_hidden;      /**< Broadcast SSID or not, default 0, broadcast the SSID */
    uint8 max_connection;   /**< Max number of stations allowed to connect in, default 4, max 4 */
    uint16 beacon_interval; /**< Beacon interval, 100 ~ 60000 ms, default 100 */

	static struct softap_config config_ap = 
	{
		.ssid = ACCESS_POINT_SSID,
		.ssid_len = 0,
		.password = ACCESS_POINT_PASSKEY,
		.channel = 1,
		.authmode = AUTH_WPA_WPA2_PSK,
		.ssid_hidden = 0,	//broadcast SSID
		.max_connection = 1,
		.beacon_interval = 100
	};

	static struct ip_info ip_ap;
	IP4_ADDR(&ip_ap.ip, 192, 168, 1, 1);
	IP4_ADDR(&ip_ap.gw, 192, 168, 1, 1);
	IP4_ADDR(&ip_ap.netmask, 255, 255, 255, 0);

	static struct dhcps_lease dhcp_ap = 
	{
		.enable = true,	
	};
	IP4_ADDR(&dhcp_ap.start_ip, 192, 168, 1, 2);
	IP4_ADDR(&dhcp_ap.end_ip, 192, 168, 1, 10);


	printf("In task %s\r\n", __func__);

	if(!wifi_set_opmode(STATIONAP_MODE))
	{
		/* could not set operation mode */
		printf("Error in %s - Could not set operation mode!\r\n", __func__);
		vTaskDelete(NULL); 
	}

	printf("##### 0 #####\r\n");

	if(!wifi_softap_set_config(&config_ap))
	{
		/* could not set station configuration */
		printf("Error in %s - Could not set access point configuration!\r\n", __func__);
		vTaskDelete(NULL); 
	}

	printf("##### 1 #####\r\n");

	/* set access point IP and DHCP configuration */
	if(wifi_softap_dhcps_stop())
	{
		printf("##### 2 #####\r\n");
		if(!wifi_set_ip_info(SOFTAP_IF, &ip_ap))
		{
			/* could not set station ip configuration */
			printf("Error in %s - Could not set access point ip configuration!\r\n", __func__);
			vTaskDelete(NULL); 
		}

		printf("##### 3 #####\r\n");

		if(!wifi_softap_set_dhcps_lease(&dhcp_ap))
		{
			/* could not set access point DHCP configuration */
			printf("Error in %s - Could not set access point DHCP configuration!\r\n", __func__);
			vTaskDelete(NULL); 
		}

		printf("##### 4 #####\r\n");
 
		if(!wifi_softap_dhcps_start())
		{
			/* could not start access point DHCP */
			printf("Error in %s - Could not start access point DHCP!\r\n", __func__);
			vTaskDelete(NULL); 
		}

		printf("##### 5 #####\r\n");
	}
	else
	{
		/* could not stop access point DHCP */
		printf("Error in %s - Could not stop access point DHCP!\r\n", __func__);
		vTaskDelete(NULL); 
	}

	/* register callback for WiFi events */
	if(!wifi_set_event_handler_cb(wifi_handle_event_cb))
	{
		/* could not set WiFi event callback */
		printf("Error in %s - Could not set Wi-Fi event callback!\r\n", __func__);
		vTaskDelete(NULL); 
	}

	vTaskDelete(NULL); 
}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void ICACHE_FLASH_ATTR
user_init(void)
{
	uart_init_new();
	os_delay_us(10000);
	printf("SDK version:%s\n", system_get_sdk_version());
	xTaskCreate(task_display, "Seven Segment Display Task", 256, NULL, 2, NULL); 
    xTaskCreate(task_reset, "Reset Task", 256, NULL, 2, NULL);
	xTaskCreate(task_wireless, "Wi-Fi Management Task", 512, NULL, 2, NULL);
}

