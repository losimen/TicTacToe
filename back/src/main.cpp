#include <Arduino.h>
#include <ArduinoJson.h>

int board[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
int turn = 0;
bool isEnded = false;
bool isTie = false;

void resetBoard()
{
  for (int i = 0; i < 9; i++)
  {
    board[i] = -1;
  }

  turn = 0;
  isEnded = false;
  isTie = false;
}



void setup() 
{
  Serial.begin(9600);
  Serial.setTimeout(50);
}


void loop() {

  if (Serial.available() > 0) {
    String json = Serial.readStringUntil('\n');
    DynamicJsonDocument doc(1024);

    deserializeJson(doc, json);
    const char* sensor = doc["sensor"];
    
    Serial.println(sensor);
  }
  delay(1000);
}
