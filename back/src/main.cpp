#include <Arduino.h>
#include <ArduinoJson.h>
#include <Game.h>

Game game;

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
      game.resetBoard();
    }
    else if (action == "mark-slot")
    {
      game.makeTurn((*doc)["id"].as<int>());
    }
    else 
    {
      // {"action": "hi"}
      // Serial.println("Invalid action");
    }

    delete doc;
    DynamicJsonDocument *jsonResult = new DynamicJsonDocument(700);

    for (int i = 0; i < 9; i++)
    {
      (*jsonResult)["board"][i] = game.board[i];
    }
    (*jsonResult)["turn"] = game.turn;
    (*jsonResult)["isEnded"] = game.isEnded;
    (*jsonResult)["isTie"] = game.isTie;

    String stringResult;
    serializeJson((*jsonResult), stringResult);

    delete jsonResult;

    stringResult += "^";

    Serial.println(stringResult);
  }

  delay(100);
}
