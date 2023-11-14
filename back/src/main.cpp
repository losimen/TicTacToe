#include <Arduino.h>

void setup() 
{
  Serial.begin(9600);
  Serial.setTimeout(50);
}


void loop() {
  Serial.println("log");
  delay(1000);
}
