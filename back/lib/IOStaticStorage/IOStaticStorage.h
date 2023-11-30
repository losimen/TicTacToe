#include <EEPROM.h>

class IOStaticStorage
{
private:
    const int BOARD_LENGTH;

public:
    IOStaticStorage() : BOARD_LENGTH(9)
    {
        // Additional setup if needed
    }

    void writeBoard(int board[9], bool isEnded, bool isTie)
    {
        for (int i = 0; i < BOARD_LENGTH; i++)
        {
            EEPROM.put(i * sizeof(unsigned int), board[i]);
        }

        const unsigned int END_BOARD_ADDRESS = BOARD_LENGTH * sizeof(unsigned int);

        EEPROM.put(END_BOARD_ADDRESS, isEnded);
        EEPROM.put(END_BOARD_ADDRESS + sizeof(bool), isTie);
    }

    void readBoard(int board[9], bool &isEnded, bool &isTie)
    {
        for (int i = 0; i < BOARD_LENGTH; i++)
        {
            EEPROM.get(i * sizeof(unsigned int), board[i]);
        }

        const unsigned int END_BOARD_ADDRESS = BOARD_LENGTH * sizeof(unsigned int);

        EEPROM.get(END_BOARD_ADDRESS, isEnded);
        EEPROM.get(END_BOARD_ADDRESS + sizeof(bool), isTie);
    }
};
