#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(LifoBuffer)
{
  RUN_TEST_CASE(LifoBuffer, create_lifo_buffer_success_1);
  RUN_TEST_CASE(LifoBuffer, create_lifo_buffer_fail_length_0_2);
  RUN_TEST_CASE(LifoBuffer, create_lifo_buffer_fail_buffer_null_3);
  RUN_TEST_CASE(LifoBuffer, create_lifo_buffer_add_word_full_4);
  RUN_TEST_CASE(LifoBuffer, create_lifo_buffer_add_word_not_full_5);
  RUN_TEST_CASE(LifoBuffer, print_lifo_buffer_fail_6);
  RUN_TEST_CASE(LifoBuffer, print_lifo_buffer_casio_success_7);
  RUN_TEST_CASE(LifoBuffer, destroy_lifo_buffer_8);
}

TEST_GROUP_RUNNER(FifoBuffer)
{
  RUN_TEST_CASE(FifoBuffer, create_fifo_buffer_fail_buffer_null_1);
  RUN_TEST_CASE(FifoBuffer, create_fifo_buffer_fail_length_0_2);
  RUN_TEST_CASE(FifoBuffer, create_fifo_buffer_success_3); 
  RUN_TEST_CASE(FifoBuffer, create_fifo_buffer_add_word_not_full_4);
  RUN_TEST_CASE(FifoBuffer, create_fifo_buffer_add_word_full_overwrite_5);
  RUN_TEST_CASE(FifoBuffer, create_fifo_buffer_add_word_full_6);
  RUN_TEST_CASE(FifoBuffer, partial_remove_from_full_fifo_buffer_7);
  RUN_TEST_CASE(FifoBuffer, remove_until_empty_from_not_full_fifo_buffer_8);
  RUN_TEST_CASE(FifoBuffer, remove_until_empty_from_full_fifo_buffer_9);
  RUN_TEST_CASE(FifoBuffer, print_fifo_buffer_casio_success_10);
  RUN_TEST_CASE(FifoBuffer, print_fifo_buffer_fail_11);
  RUN_TEST_CASE(FifoBuffer, destroy_fifo_buffer_12);
  RUN_TEST_CASE(FifoBuffer, add_remove_add_fifo_buffer_13);
}