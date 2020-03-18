ESP8266 WIFI MODULE
------------------------------


* [ESPRESSIF(Worlwide)](https://www.espressif.com/en/products/hardware/modules)
* [Datasheet and AT command](https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf)


## Features

* High-performance 160 MHz single-core CPU
* +19.5 dBm output at the antenna ensures a good physical range
* Sleep current is less than 20 μA, making it suitable for battery-powered 
and wearable-electronics applications
* Peripherals include UART, GPIO, I2C, I2S, SDIO, PWM, ADC and SPI
* Fully certified with integrated antenna and software stacks


## ESP8266 Pinout

		RX      * *    VCC
		GPIO0   * *    RESET
		GPIO2   * *    EN
		GND     * *    TX


## Settings

* ESP_SSID=""
	> Name of wifi
* ESP_Password="password of wifi"
	> Password of wifi

* Sleep_Time=""			
	> The duration of ESP8266’s sleep. Unit: ms.

* identifier="" 		
	> This command ATE is used to trigger command echo
				0: Switches echo off
				1: Switches echo on.

* Esp_Mode=""			
	> The configuration changes will be saved in the system parameter area in the flash.
				1: Station Mode
				2: AP mode Host
				3:AP+Station mode
* SAP_SSID="ESP8266"		
* SAP_Password="123456"
* SAP_Channel="2"		
	> 1 cause unknown problem
* SAP_Enc=""			
				1: OPEN, 
				2: WPA_PSK, 
				3: WPA2_PSK, 
				4: WPA_WPA2_PSK

* DHCP_Mode=""			
	> The configuration changes will be stored in the user parameter area in the flash. 
				0: Sets ESP8266 SoftAP
				1: Sets ESP8266 Station 
				2: Sets both SoftAP and Station 
* DHCP_En=""			
				0: Disables DHCP

* MAC_Adress=""			
	> Sets the MAC Address of the ESP8266 SoftAP

* IP_Adress=""			
	> Sets the Current IP Address of the ESP8266 Station

* Type=""			
	> String parameter indicating the connection type: "TCP", "UDP"	or "SSL".
* Addr=""			
	> String parameter indicating the remote IP address
* Port=""			
	> The remote port number. 

* TCP_USP_ID=""			
	> ID of the connection (0~4), for multiple connections. 
* Multiple_Length=""		
	> Data length, MAX: 2048 bytes. 

* CIPMUX_Mode=""		
				0: single connection
				1: multiple connections

* CIPSERVER_Mode=""
				0: deletes server
				1: creates server
* CIPSERVER_Port=""		port number; 333 by default.
* CIP_Mode=""			
				0: normal transmission mode. 
				1: UART-Wi-Fi passthrough mode (transparent transmission), which can only be enabled in TCP
				single connection mode or in UDP mode when the remote IP and port do not change.
* Timeout=""			
	> TCP server timeout within the range of 0 ~ 7200s



## Example

```c 
String Esp_SSID = "Nucleo_ArGe"; //Enter SSID
String Esp_Password = "NucleoArGe123654"; //Enter Password
String Esp_Mode="1";
String TCP_USP_ID=""; 

int initial()
{
  Test_Module();
  delay(500);
  Restart_Module();
  delay(500);
  Set_Mode();
  Connect_AP();
}
```
