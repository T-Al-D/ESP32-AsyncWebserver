#include <unity.h>

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_example(void)
{
    // Test assertion
    TEST_ASSERT_EQUAL(1, 1);
}

void test_example2(void)
{
    TEST_ASSERT_NOT_EQUAL(1, 0);
}

int main(int argc, char** argv)
{
    UNITY_BEGIN();

    //Run your test functions here
    RUN_TEST(test_example);
    RUN_TEST(test_example2);

    UNITY_END();
    return 0;
}