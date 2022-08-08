/******************************************************************************************
 * FileName     : etboard_simple_mqtt.h
 * Description  : ETboard Simple MQTT
 * Author       : SCS
 * Created Date : 2022.08.06
 * Reference    : 
 * Modified     : 
 * Modified     : 
******************************************************************************************/

#ifndef ETBOARD_SIMPLE_MQTT_H
#define ETBOARD_SIMPLE_MQTT_H

#include <Arduino.h>
//#include <String>
#include <ArduinoJson.h>

class ETBOARD_SIMPLE_MQTT {

  private:	
    
  
  public:
    String mqtt_prefix;
    String mac_address;
    
  	ETBOARD_SIMPLE_MQTT();
    
    void setup(
      const char* mqttServerIp,
      const short mqttServerPort,
      const char* mqttUsername,
      const char* mqttPassword,
      const char* mqttClientName);  
      
    void setup_with_wifi(
      const char* wifiSsid,
      const char* wifiPassword,
      const char* mqttServerIp,
      const char* mqttUsername,
      const char* mqttPassword,
      const char* mqttClientName,
      const short mqttServerPort);    
      
    String get_topic_prefix(void);
    void onConnectionEstablished(void);
    void send_analog_a0(void);
    void publish(const String &topic, const String &payload);
    void send_analog(void);
    void send_digital(void);
    void recv_digital(void);
    boolean is_changed_digital(void);
    void loop(void);
};

#endif

//=================================================================================
// End of Line
//=================================================================================