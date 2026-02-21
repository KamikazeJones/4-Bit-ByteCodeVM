#include "unity.h"
#include "interpreter.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_interpreter_add(void) {
    UNITY_TEST_ASSERT_EQUAL_INT(16, add(7,9), __LINE__,"7+9 sollte 16 ergeben, Fehler beim addieren!");
}
/*
void test_interpreter_string(void) {
    //test stuff
}

void test_interpreter_file(void) {
    //more test stuff
}
*/

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_interpreter_add);
    return UNITY_END();
}