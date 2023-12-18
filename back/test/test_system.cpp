#include <unity.h>
#include <Game.h>
#include <ArduinoJson.h>
#include <IOStaticStorage.h>


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_check_win_player1(void) {
    Game game;
    game.makeHumanTurn(0);
    game.makeHumanTurn(3);
    game.makeHumanTurn(1);
    game.makeHumanTurn(4);
    game.makeHumanTurn(2);

    TEST_ASSERT_EQUAL(true, game.isEnded);
    TEST_ASSERT_EQUAL(false, game.isTie);
    TEST_ASSERT_EQUAL(0, game.turn % 2);
}


void test_check_win_player2(void) {
    Game game;
    game.makeHumanTurn(0);
    game.makeHumanTurn(3);
    game.makeHumanTurn(1);
    game.makeHumanTurn(4);
    game.makeHumanTurn(6);
    game.makeHumanTurn(5);

    TEST_ASSERT_EQUAL(true, game.isEnded);
    TEST_ASSERT_EQUAL(false, game.isTie);
    TEST_ASSERT_EQUAL(1, game.turn % 2);
}


void test_check_tie(void) {
    Game game;
    game.makeHumanTurn(0);
    game.makeHumanTurn(1);
    game.makeHumanTurn(2);
    game.makeHumanTurn(4);
    game.makeHumanTurn(3);
    game.makeHumanTurn(5);
    game.makeHumanTurn(7);
    game.makeHumanTurn(6);
    game.makeHumanTurn(8);

    TEST_ASSERT_EQUAL(true, game.isEnded);
    TEST_ASSERT_EQUAL(true, game.isTie);
}


void test_check_json(void)
{
    char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, json);

    const char* sensor = doc["sensor"];
    
    TEST_ASSERT_EQUAL_STRING("gps", sensor);
}

void test_check_static_io(void)
{
    IOStaticStorage io;
    int board[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    io.writeBoard(board, false, false, 0);

    int board2[9];
    bool isEnded;
    bool isTie;
    int turn;
    io.readBoard(board2, isEnded, isTie, turn);

    for (int i = 0; i < 9; i++)
    {
        TEST_ASSERT_EQUAL(board[i], board2[i]);
    }

    TEST_ASSERT_EQUAL(false, isEnded);
    TEST_ASSERT_EQUAL(false, isTie);
    TEST_ASSERT_EQUAL(0, turn);
}


int main( int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_check_win_player1);
    RUN_TEST(test_check_win_player2);
    RUN_TEST(test_check_tie);

    RUN_TEST(test_check_json);

    UNITY_END();
}