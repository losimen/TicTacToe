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
        delete doc;
    }
    else if (action == "change-game-mode")
    {
        const GameMode gameMode = (GameMode)(*doc)["gameMode"].as<int>();
        delete doc;
        game.gameMode = gameMode;
        status = "success";
    }
    else if (action == "ai-move")
    {
        status = game.makeAITurn();
        delete doc;
    }
    
    else if (action == "mark-slot")
    {
        const int id = (*doc)["id"].as<int>();
        delete doc;
        status = game.makeHumanTurn(id);
    }
    else if (action == "synchronize")
    {
        restoreFromStorage();
        delete doc;
        status = "success";
    }
    else
    {
        delete doc;
        // {"action": "hi"}
        // Serial.println("Invalid action");
    }

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