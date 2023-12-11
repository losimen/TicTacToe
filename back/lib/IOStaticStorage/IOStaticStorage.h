#include <EEPROM.h>

/// @brief This class is responsible for the IO operations with the EEPROM
/// @details This class called by the Pool class
class IOStaticStorage
{
private:
    /// @brief The length of the board array. Game is 3x3, so 9
    const int BOARD_LENGTH;

public:
    IOStaticStorage() : BOARD_LENGTH(9)
    {
        // Additional setup if needed
    }

    /// @brief Put the game state in the EEPROM
    /// @param board The board to be put in the EEPROM
    /// @param isEnded The isEnded variable to be put in the EEPROM
    /// @param isTie The isTie variable to be put in the EEPROM
    void writeBoard(int board[9], bool isEnded, bool isTie, int turn)
    {
        for (int i = 0; i < BOARD_LENGTH; i++)
        {
            EEPROM.put(i * sizeof(unsigned int), board[i]);
        }

        const unsigned int END_BOARD_ADDRESS = BOARD_LENGTH * sizeof(unsigned int);

        EEPROM.put(END_BOARD_ADDRESS, isEnded);
        EEPROM.put(END_BOARD_ADDRESS + sizeof(bool), isTie);
        EEPROM.put(END_BOARD_ADDRESS + sizeof(bool) * 2, turn);
    }

    /// @brief Get the game state from the EEPROM
    /// @param board The board to be filled with the data from the EEPROM
    /// @param isEnded The isEnded variable to be filled with the data from the EEPROM
    /// @param isTie The isTie variable to be filled with the data from the EEPROM
    /// @param turn The turn variable to be filled with the data from the EEPROM
    void readBoard(int board[9], bool &isEnded, bool &isTie, int &turn)
    {
        for (int i = 0; i < BOARD_LENGTH; i++)
        {
            EEPROM.get(i * sizeof(unsigned int), board[i]);
        }

        const unsigned int END_BOARD_ADDRESS = BOARD_LENGTH * sizeof(unsigned int);

        EEPROM.get(END_BOARD_ADDRESS, isEnded);
        EEPROM.get(END_BOARD_ADDRESS + sizeof(bool), isTie);
        EEPROM.get(END_BOARD_ADDRESS + sizeof(bool) * 2, turn);
    }
};
