/******************************************************************************************
 * FileName     : app_config.h
 * Description  : 응용 프로그램 구성 
 * Author       : SCS
 * Created Date : 2022.08.06
 * Reference    : 
 * Modified     : 
 * Modified     : 
******************************************************************************************/

#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "lib/etboard_com.h"
#include "lib/etboard_simple_mqtt.h"
#include "lib/etboard_oled_u8g2.h"

//==========================================================================================
class APP_CONFIG 
//==========================================================================================
{

  private:  
    //String lineString[3];
  
  public:
    const char* board_firmware_verion = "etb_temp_v0.9";
    unsigned lastMillis;//
    ETBOARD_OLED_U8G2 oled;
    ETBOARD_COM etboard;
    ETBOARD_SIMPLE_MQTT mqtt;
    
    APP_CONFIG();
    void setup(void);    
    void fast_blink_led(void);
    void normal_blink_led(void); 
    void display_BI(void);
    
};

#endif

//==========================================================================================
// End of Line
//==========================================================================================
