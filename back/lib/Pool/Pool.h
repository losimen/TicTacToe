// TODO: don't like that we import in the header. Possibly it is not fixable using the current architecture PIO
#include <Arduino.h>
#include <Game.h>

class Pool
{
private:
    Game game;

public:
    String accept(String json);
};