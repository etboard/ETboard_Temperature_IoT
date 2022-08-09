#include <ArduinoJson.h>

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  while (!Serial) continue;
  
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject(); 
  
  JsonArray& values = JSONencoder.createNestedArray("values");

  int sensorValue = 0; 
  sensorValue = analogRead(A0); values.add(sensorValue);
  sensorValue = analogRead(A1); values.add(sensorValue);
  sensorValue = analogRead(A2); values.add(sensorValue);
  sensorValue = analogRead(A3); values.add(sensorValue);
  sensorValue = analogRead(A4); values.add(sensorValue);
  sensorValue = analogRead(A5); values.add(sensorValue);
 
  char JSONmessageBuffer[100];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));

  Serial.println("json5");
  Serial.println(JSONmessageBuffer);
}

void loop() {
  // put your main code here, to run repeatedly:

}
