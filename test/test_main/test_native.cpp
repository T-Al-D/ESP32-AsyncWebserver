#include <unity.h>

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_Example(void)
{
    TEST_ASSERT_EQUAL(true, true);
}

int main(int argc, char** argv)
{
    UNITY_BEGIN();

    // Run your test functions here
    RUN_TEST(test_Example);

    UNITY_END();
    return 0;
}