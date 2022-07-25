/******************************************************************************************
 * FileName     : temperature_iot.ino
 * Description  : 이티보드로 온도를 측정하여 스마트폰으로 확인
 * Author       : SCS
 * Created Date : 2022.07.20
 * Reference    : 
 * Modified     : 
 * Modified     : 
******************************************************************************************/

//==========================================================================================
// Firmware Version
//==========================================================================================
const char* board_hardware_verion = "ETBoard_V1.1";
const char* board_firmware_verion = "etb_temp_v0.9";

//==========================================================================================
// Include Common
//==========================================================================================
#include "oled_u8g2.h"
OLED_U8G2 oled;

#include "etboard_com.h"
ETBOARD_COM etb;

#include "etboard_simple_mqtt.h"
ETBOARD_SIMPLE_MQTT mqtt;

//==========================================================================================
// Include custom
//==========================================================================================
#include "DHT.h"

#define DHTPIN D9     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

//==========================================================================================
// Declaration
//==========================================================================================
const uint16_t NORMAL_SEND_INTERVAL = 1000 * 5;

static unsigned lastMillis = 0;

//==========================================================================================
void setup()
//==========================================================================================
{
  //----------------------------------------------------------------------------------------
  // etboard
  //----------------------------------------------------------------------------------------  
  etb.setup();
  etb.fast_blink_led();
  etb.print_board_information(board_hardware_verion, board_firmware_verion);    

  //----------------------------------------------------------------------------------------
  // oled
  //----------------------------------------------------------------------------------------
  oled.setup();
  display_BI();  

  //----------------------------------------------------------------------------------------
  // mqtt
  //----------------------------------------------------------------------------------------
  mqtt.setup();

  //----------------------------------------------------------------------------------------
  // initialize variables
  //----------------------------------------------------------------------------------------
  lastMillis = millis();
}


//==========================================================================================
void loop()
//==========================================================================================
{
  //----------------------------------------------------------------------------------------
  // MQTT loop
  //----------------------------------------------------------------------------------------
  mqtt.loop();
    
  //----------------------------------------------------------------------------------------
  //  Send sensor value
  //----------------------------------------------------------------------------------------
  if (millis() - lastMillis > NORMAL_SEND_INTERVAL) {  
      mqtt.send_analog();
      //mqtt.send_digital();
      send_temperature();
      display_Information();
      lastMillis = millis();
   }  

  //----------------------------------------------------------------------------------------
  //  Send digital sensor value if changed
  //----------------------------------------------------------------------------------------    
   if (mqtt.is_changed_digital() == true) {
      mqtt.send_digital();
      test1();
   }
  
  //----------------------------------------------------------------------------------------
  // Blink Operation LED
  //----------------------------------------------------------------------------------------  
  etb.normal_blink_led();
}


//==========================================================================================
void onConnectionEstablished()
//==========================================================================================
{
  mqtt.onConnectionEstablished();
}


//==========================================================================================
void display_BI() 
//==========================================================================================
{
  oled.setLine(1,"<ketri.re.kr>");
  oled.setLine(2,"Welcome to");
  oled.setLine(3," ET-Board");
  oled.display();  
}

//==========================================================================================
void display_Information() 
//==========================================================================================
{
  
  float t = dht.readTemperature();  
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  String string_t = String(t, 2); 
  
  oled.setLine(1,board_firmware_verion);
  oled.setLine(2,"M:" + mqtt.mac_address.substring(9));
  oled.setLine(3,"T:" + string_t);
  oled.display();  
}

//==========================================================================================
void test1()
//==========================================================================================
{  
  int sensorValue = 0; 
  sensorValue = analogRead(A0);
  mqtt.publish("/a0", String(sensorValue));
}

//==========================================================================================
void send_temperature()
//==========================================================================================
{ 
  float h = dht.readHumidity();  
  float t = dht.readTemperature();  

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  String string_t = String(t, 2); 
  mqtt.publish("/temperature", String(string_t));
}


//==========================================================================================
//                                                    
// (주)한국공학기술연구원 http://et.ketri.re.kr       
//                                                    
//==========================================================================================
