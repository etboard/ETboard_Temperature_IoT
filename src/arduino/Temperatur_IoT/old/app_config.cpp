/******************************************************************************************
 * FileName     : app_config.cpp
 * Description  : 응용 프로그램 구성 
 * Author       : SCS
 * Created Date : 2022.08.06
 * Reference    : 
 * Modified     : 
 * Modified     : 
******************************************************************************************/

#include "app_config.h"

//==========================================================================================
// Include Componet header
//==========================================================================================
#include "lib/etboard_oled_u8g2.h"
#include "lib/etboard_oled_u8g2.cpp"
//OLED_U8G2 oled;

#include "lib/etboard_com.h"
#include "lib/etboard_com.cpp"
//ETBOARD_COM etboard;

#include "lib/etboard_wifi.h"
#include "lib/etboard_wifi.cpp"
ETBOARD_WIFI wifi;

#include "lib/etboard_simple_mqtt.h"
#include "lib/etboard_simple_mqtt.cpp"
//ETBOARD_SIMPLE_MQTT mqtt;

//==========================================================================================
// Declaration
//==========================================================================================

//static unsigned lastMillis = 0;

//==========================================================================================
// Firmware Version
//==========================================================================================
const char* board_hardware_verion = "ETBoard_V1.1";
//const char* board_firmware_verion = "etb_temp_v0.9";


//=================================================================================
APP_CONFIG::APP_CONFIG() 
//=================================================================================	
{
  lastMillis = 0;
}

//=================================================================================
void APP_CONFIG::setup(void) 
//=================================================================================
{
   //----------------------------------------------------------------------------------------
  // etboard
  //----------------------------------------------------------------------------------------  
  etboard.setup();
  etboard.fast_blink_led();
  etboard.print_board_information(board_hardware_verion, board_firmware_verion);    

  //----------------------------------------------------------------------------------------
  // oled
  //----------------------------------------------------------------------------------------
  oled.setup();
  display_BI();  

  //----------------------------------------------------------------------------------------
  // wifi
  //----------------------------------------------------------------------------------------
  etboard.wifi_setup_start_led();
  wifi.setup();
  delay(500);
  etboard.wifi_setup_end_led();

  //----------------------------------------------------------------------------------------
  // mqtt
  //----------------------------------------------------------------------------------------  
  mqtt.setup(wifi.mqtt_server,       // MQTT Broker server ip
             atoi(wifi.mqtt_port),   // The MQTT port, default to 1883. this line can be omitted);
             wifi.mqtt_user,         // Can be omitted if not needed  // Username
             wifi.mqtt_pass,         // Can be omitted if not needed  // Password
             "");                    // Client name that uniquely identify your device

  //----------------------------------------------------------------------------------------
  // initialize variables
  //----------------------------------------------------------------------------------------
  lastMillis = millis();
}

//=================================================================================
void APP_CONFIG::fast_blink_led(void) 
//=================================================================================
{
  for(int i=0; i<10; i++) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);                         // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(50);                         // wait for a second
  }
}

//==========================================================================================
void APP_CONFIG::display_BI(void) 
//==========================================================================================
{
  oled.setLine(1,"<ketri.re.kr>");
  oled.setLine(2,"Welcome to");
  oled.setLine(3," ET-Board");
  oled.display();  
}

//=================================================================================
// End of Line
//=================================================================================
