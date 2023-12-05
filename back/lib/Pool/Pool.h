// TODO: don't like that we import in the header. Possibly it is not fixable using the current architecture PIO
#include <Arduino.h>
#include <Game.h>
#include <IOStaticStorage.h>

class Pool
{
private:
    Game game;
    IOStaticStorage storage;

public:
    String accept(String json);

    void restoreFromStorage();
};