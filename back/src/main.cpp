#include <Arduino.h>
#include <TagWorker.h>

void setup() 
{
  Serial.begin(9600);
  Serial.setTimeout(50);
}


void loop() {

  if (Serial.available())
  {
    TagWorker tagWorker(Serial.readString());
    String response = tagWorker.getKeyValue("key");

    Serial.println("log");
    Serial.println(response);
  }
}
