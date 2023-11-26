#include <ArduinoJson.h>

#include "Pool.h"

String Pool::accept(String json)
{
    DynamicJsonDocument *doc = new DynamicJsonDocument(700);

    deserializeJson(*doc, json);
    String action = (*doc)["action"].as<String>();
    String status = "unknown";
    if (action == "reset-board")
    {
        status = game.resetBoard();
    }
    else if (action == "mark-slot")
    {
        status = game.makeTurn((*doc)["id"].as<int>());
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

    (*jsonResult)["status"] = status;
    (*jsonResult)["turn"] = game.turn;
    (*jsonResult)["isEnded"] = game.isEnded;
    (*jsonResult)["isTie"] = game.isTie;

    String stringResult;
    serializeJson((*jsonResult), stringResult);

    delete jsonResult;

    stringResult += "^";

    return stringResult;
}