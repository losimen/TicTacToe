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

void makeTurn(int id)
{
  if (isEnded || board[id] != -1)
  {
    return;
  }

  int mark = turn % 2;
  board[id] = mark;

  turn += 1;
}


void setup() 
{
  Serial.begin(38400);
  Serial.setTimeout(50);
}


void loop() {

  if (Serial.available() > 0) {
    String json = Serial.readStringUntil('\n');
    DynamicJsonDocument *doc = new DynamicJsonDocument(700);

    deserializeJson(*doc, json);
    String action = (*doc)["action"].as<String>();

    if (action == "reset-board")
    {
      resetBoard();
    }
    else if (action == "mark-slot")
    {
      makeTurn((*doc)["id"].as<int>());
    }
    else 
    {
      // {"action": "hi"}
      // Serial.println("Invalid action");
    }

    delete doc;
    DynamicJsonDocument *result = new DynamicJsonDocument(700);

    for (int i = 0; i < 9; i++)
    {
      (*result)["board"][i] = board[i];
    }
    (*result)["turn"] = turn;
    (*result)["isEnded"] = isEnded;
    (*result)["isTie"] = isTie;

    String ready;
    serializeJson((*result), ready);

    delete result;

    ready += "^";

    Serial.println(ready);
  }

  delay(100);
}
