// TODO: don't like that we import in the header
#include <Arduino.h>
#include <Game.h>

class Pool
{
private:
    Game game;

public:
    String accept(String json);
};