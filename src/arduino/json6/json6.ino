#include <ArduinoJson.h>

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  while (!Serial) continue;
  
  StaticJsonDocument<300> doc;
  
  JsonArray data = doc.createNestedArray("values");

  int sensorValue = 0; 
  sensorValue = analogRead(A0); data.add(sensorValue);
  sensorValue = analogRead(A1); data.add(sensorValue);
  sensorValue = analogRead(A2); data.add(sensorValue);
  sensorValue = analogRead(A3); data.add(sensorValue);
  sensorValue = analogRead(A4); data.add(sensorValue);
  sensorValue = analogRead(A5); data.add(sensorValue);

  Serial.println("json6");
  String output;
  serializeJson(doc, output);
  Serial.println(output);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
