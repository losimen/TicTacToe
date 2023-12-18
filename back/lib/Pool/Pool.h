// TODO: don't like that we import in the header. Possibly it is not fixable using the current architecture PIO
#include <Arduino.h>
#include <Game.h>
#include <IOStaticStorage.h>

/// @brief This class is responsible for the accepting the JSON requests and returning the JSON responses
/// @details It is entry point for the application to communicate with other abstractions
class Pool
{
private:
    /// @brief The game state
    Game game;
    /// @brief The IOStaticStorage communication class
    IOStaticStorage storage;

public:
    /// @brief accepts the JSON request, delegates the request to the appropriate method and parses request
    /// @param json The JSON request
    /// @return The JSON response
    String accept(String json);

    /// @brief Resets the board to the initial state. Runs only at the start of the game
    void restoreFromStorage();
};