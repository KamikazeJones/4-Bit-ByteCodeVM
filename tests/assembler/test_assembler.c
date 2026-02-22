#include "unity.h"
#include "assembler.h"
#include "dyn_bytearray.h"

void setUp(void) {}
void tearDown(void) {}

void test_assemble_empty(void)
{
    dyn_bytearray_t buf;
    dba_init(&buf, 2, 2);
    TEST_ASSERT_EQUAL_INT(0, assemble("", &buf));
    TEST_ASSERT_EQUAL_UINT32(0, buf.size);
    dba_free(&buf);
}

void test_assemble_push_and_opcode(void)
{
    dyn_bytearray_t buf;
    dba_init(&buf, 2, 2);
    /* valid program: push 0x0F then add and duplicate ("+AD" => AD op twice?) */
    TEST_ASSERT_EQUAL_INT(0, assemble("$0F+AD", &buf));
    /* expected bytes: opcode PS (0) padded -> 0x00, immediate 0x0F,
       then two opcodes + (AD) -> AD=0x6 nibble, packed twice yields 0x66 */
    TEST_ASSERT_EQUAL_UINT32(3, buf.size);
    TEST_ASSERT_EQUAL_UINT8(0x00, buf.data[0]);
    TEST_ASSERT_EQUAL_UINT8(0x0F, buf.data[1]);
    TEST_ASSERT_EQUAL_UINT8(0x66, buf.data[2]);
    dba_free(&buf);
}

void test_assemble_unknown(void)
{
    dyn_bytearray_t buf;
    dba_init(&buf, 2, 2);
    /* unrecognized token should return error */
    TEST_ASSERT_EQUAL_INT(-1, assemble("!?", &buf));
    dba_free(&buf);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_assemble_empty);
    RUN_TEST(test_assemble_push_and_opcode);
    RUN_TEST(test_assemble_unknown);
    return UNITY_END();
}
