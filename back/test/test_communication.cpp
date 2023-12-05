#include <unity.h>
#include <ArduinoJson.h>


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_circular_buffer_empty_after_init() {
    // char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

    // DynamicJsonDocument doc(1024);
    // deserializeJson(doc, json);

    // const char* sensor = doc["sensor"];

    // Serial.println("log");

    // TEST_ASSERT_EQUAL_STRING("gps", sensor);
    TEST_ASSERT_TRUE(true);
}

void test_json_data()
{
    char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, json);

    const char* sensor = doc["sensor"];
    
    TEST_ASSERT_EQUAL_STRING("gps", sensor);
}


int main( int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_circular_buffer_empty_after_init);
    RUN_TEST(test_json_data);

    UNITY_END();
}