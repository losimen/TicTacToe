#include <Arduino.h>
#include <ArduinoJson.h>
#include <Pool.h>

Pool pool;

void setup() 
{
  Serial.begin(38400);
  Serial.setTimeout(50);
}

void loop() 
{

  if (Serial.available() > 0) 
  {
    String result = pool.accept(Serial.readStringUntil('^'));
    Serial.println(result);
  }

  delay(100);
}
