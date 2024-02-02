#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(LifoBuffer)
{
  RUN_TEST_CASE(LifoBuffer, create_buffer_success_1);
  RUN_TEST_CASE(LifoBuffer, create_buffer_fail_length_0_2);
  RUN_TEST_CASE(LifoBuffer, create_buffer_fail_buffer_null_3);
  RUN_TEST_CASE(LifoBuffer, create_buffer_add_word_full_4);
  RUN_TEST_CASE(LifoBuffer, create_buffer_add_word_not_full_5);
}