#include <ArduinoJson.h>

#include "Pool.h"

void Pool::restoreFromStorage()
{
    storage.readBoard(game.board, game.isEnded, game.isTie, game.turn);
}

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
    else if (action == "change-game-mode")
    {
        game.gameMode = (GameMode)(*doc)["gameMode"].as<int>();
        status = "success";
    }
    else if (action == "ai-move")
    {
        status = game.makeAITurn();
    }
    
    else if (action == "mark-slot")
    {
        status = game.makeHumanTurn((*doc)["id"].as<int>());
    }
    else if (action == "synchronize")
    {
        restoreFromStorage();
        status = "success";
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

    (*jsonResult)["gameMode"] = game.gameMode;
    (*jsonResult)["status"] = status;
    (*jsonResult)["turn"] = game.turn;
    (*jsonResult)["isEnded"] = game.isEnded;
    (*jsonResult)["isTie"] = game.isTie;

    storage.writeBoard(game.board, game.isEnded, game.isTie, game.turn);

    String stringResult;
    serializeJson((*jsonResult), stringResult);

    delete jsonResult;

    stringResult += "^";

    return stringResult;
}