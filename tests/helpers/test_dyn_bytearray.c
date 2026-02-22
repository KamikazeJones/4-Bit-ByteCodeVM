#include "unity.h"
#include "dyn_bytearray.h"

void setUp(void) {}
void tearDown(void) {}

void test_init_and_free(void)
{
    dyn_bytearray_t buf;
    TEST_ASSERT_EQUAL_INT(0, dba_init(&buf, 5, 3));
    TEST_ASSERT_NOT_NULL(buf.data);
    TEST_ASSERT_EQUAL_UINT32(0, buf.size);
    TEST_ASSERT_EQUAL_UINT32(5, buf.capacity);
    dba_free(&buf);
}

void test_append_and_growth(void)
{
    dyn_bytearray_t buf;
    dba_init(&buf, 2, 2);
    TEST_ASSERT_EQUAL_INT(0, dba_append(&buf, 0x11));
    TEST_ASSERT_EQUAL_INT(0, dba_append(&buf, 0x22));
    /* capacity still 2 */
    TEST_ASSERT_EQUAL_UINT32(2, buf.size);
    TEST_ASSERT_EQUAL_UINT32(2, buf.capacity);
    /* appending third byte forces growth by chunk size 2 */
    TEST_ASSERT_EQUAL_INT(0, dba_append(&buf, 0x33));
    TEST_ASSERT_EQUAL_UINT32(3, buf.size);
    TEST_ASSERT_EQUAL_UINT32(4, buf.capacity);
    /* values preserved */
    TEST_ASSERT_EQUAL_HEX8(0x11, buf.data[0]);
    TEST_ASSERT_EQUAL_HEX8(0x22, buf.data[1]);
    TEST_ASSERT_EQUAL_HEX8(0x33, buf.data[2]);
    dba_free(&buf);
}

void test_set_chunk(void)
{
    dyn_bytearray_t buf;
    dba_init(&buf, 1, 1);
    TEST_ASSERT_EQUAL_INT(0, dba_set_chunk(&buf, 5));
    TEST_ASSERT_EQUAL_UINT32(5, buf.chunk);
    TEST_ASSERT_EQUAL_INT(-1, dba_set_chunk(&buf, 0));
    dba_free(&buf);
}

/*
 * helper that runs a growth test with the given parameters:
 *   init     - initial buffer capacity
 *   chunk    - chunk size used for growth
 *   total    - number of append operations to perform
 *   step     - interval at which to check capacity
 */
static void run_growth_test(size_t init, size_t chunk, int total, int step)
{
    dyn_bytearray_t buf;
    dba_init(&buf, init, chunk);

    for (int i = 1; i <= total; ++i) {
        TEST_ASSERT_EQUAL_INT(0, dba_append(&buf, (uint8_t)i));
        if (i % step == 0) {
            /* compute expected capacity as in previous test */
            size_t expected_capacity = init;
            if (i > (int)init) {
                size_t extra = i - init;
                size_t chunks = (extra + chunk - 1) / chunk; /* ceil(extra/chunk) */
                expected_capacity += chunks * chunk;
            }
            TEST_ASSERT_EQUAL_UINT32(i, buf.size);
            TEST_ASSERT_EQUAL_UINT32(expected_capacity, buf.capacity);
        }
    }
    dba_free(&buf);
}

/* various scenarios exercising different parameter sets */
void test_growth_various(void)
{
    /* previous configuration (init=2,chunk=5) */
    run_growth_test(2, 5, 1000, 103);
    /* smaller chunk, more frequent growth */
    run_growth_test(2, 7, 503, 51);
    /* larger initial size, larger chunk */
    run_growth_test(10, 13, 200, 37);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_and_free);
    RUN_TEST(test_append_and_growth);
    RUN_TEST(test_set_chunk);
    RUN_TEST(test_growth_various);
    return UNITY_END();
}
