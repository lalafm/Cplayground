#include "lifo_buffer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(LifoBuffer);

//sometimes you may want to get at local data in a module.
//for example: If you plan to pass by reference, this could be useful
//however, it should often be avoided
lifo_buffer_t lifoBufferTest;

TEST_SETUP(LifoBuffer)
{
  //This is run before EACH TEST
}

TEST_TEAR_DOWN(LifoBuffer)
{
  
}

TEST(LifoBuffer, create_lifo_buffer_success_1)
{
  uint32_t length = 5u;
  create_lifo_buffer(&lifoBufferTest, length);

  //Check if correct structure was created
  TEST_ASSERT_EQUAL(length, lifoBufferTest.size);
  TEST_ASSERT_EQUAL(LIFO_FLAGS_EMPTY, lifoBufferTest.flag);
  TEST_ASSERT_EQUAL_MEMORY(lifoBufferTest.head, lifoBufferTest.base, 1);
  destroy_lifo_buffer(&lifoBufferTest);
}

TEST(LifoBuffer, create_lifo_buffer_fail_length_0_2)
{
  uint32_t length = 0u;
  create_lifo_buffer(&lifoBufferTest, length);

  //Check if correct structure was created
  TEST_ASSERT_EQUAL(length, lifoBufferTest.size);
  TEST_ASSERT_EQUAL(LIFO_FLAGS_NULL, lifoBufferTest.flag);
}

TEST(LifoBuffer, create_lifo_buffer_fail_buffer_null_3)
{
  uint32_t length = 5u;
  create_lifo_buffer(NULL, length);
  //tests runs and no seg fault occurs when sending a null buffer
}

TEST(LifoBuffer, create_lifo_buffer_add_word_full_4)
{
  char word[] = "casal";
  uint32_t length = sizeof(word);
  create_lifo_buffer(&lifoBufferTest, length);

  // act - Add word to buffer
  for(uint32_t i = 0; i < length; i++)
  {
    add_to_lifo_buffer(&lifoBufferTest, word[i]);
  }
  //assert
  TEST_ASSERT_EQUAL(length, lifoBufferTest.size);
  TEST_ASSERT_EQUAL(LIFO_FLAGS_FULL, lifoBufferTest.flag);
  TEST_ASSERT_EQUAL((length - 1), (lifoBufferTest.head - lifoBufferTest.base));
  for(uint32_t i = 0; i < length; i++)
  {
    TEST_ASSERT_EQUAL(*(lifoBufferTest.base + i), word[i]);
  }
  destroy_lifo_buffer(&lifoBufferTest);
}

TEST(LifoBuffer, create_lifo_buffer_add_word_not_full_5)
{
  char word[] = "sol";
  uint32_t wordSize = sizeof(word);
  uint32_t length = wordSize + 5u;
  create_lifo_buffer(&lifoBufferTest, length);

  // act - Add word to buffer
  for(uint32_t i = 0; i < wordSize; i++)
  {
    add_to_lifo_buffer(&lifoBufferTest, word[i]);
  }
  //assert
  TEST_ASSERT_EQUAL(length, lifoBufferTest.size);
  TEST_ASSERT_EQUAL(LIFO_FLAGS_NOT_EMPTY, lifoBufferTest.flag);
  TEST_ASSERT_EQUAL((wordSize - 1), (lifoBufferTest.head - lifoBufferTest.base));
  for(uint32_t i = 0; i < wordSize; i++)
  {
    TEST_ASSERT_EQUAL(*(lifoBufferTest.base + i), word[i]);
  }
  destroy_lifo_buffer(&lifoBufferTest);
}

TEST(LifoBuffer, print_lifo_buffer_fail_6)
{
  //arrange
  printf("From TEST(LifoBuffer, print_lifo_buffer_fail_6): ");
  create_lifo_buffer(&lifoBufferTest, 0);
  //act and assert
  print_lifo_buffer(&lifoBufferTest);
  // cleanup
  destroy_lifo_buffer(&lifoBufferTest);
}

TEST(LifoBuffer, print_lifo_buffer_casio_success_7)
{
  //arrange
  printf("From TEST(LifoBuffer, print_lifo_buffer_casio_success_10): ");
  uint8_t word[] = {'c','a','s','i','o'};
  uint32_t wordSize = sizeof(word);
  create_lifo_buffer(&lifoBufferTest, wordSize);
  for(uint32_t i = 0; i < wordSize; i++)
  {
    add_to_lifo_buffer(&lifoBufferTest, word[i]);
  }
  //act and assert
  print_lifo_buffer(&lifoBufferTest);
  // cleanup
  destroy_lifo_buffer(&lifoBufferTest);
}

TEST(LifoBuffer, destroy_lifo_buffer_8)
{
  //arrange
  uint8_t word[] = {'c','a','s','i','o'};
  uint32_t wordSize = sizeof(word);
  create_lifo_buffer(&lifoBufferTest, wordSize);
  for(uint32_t i = 0; i < wordSize; i++)
  {
    add_to_lifo_buffer(&lifoBufferTest, word[i]);
  }
  //act
  destroy_lifo_buffer(&lifoBufferTest);
  //assert
  TEST_ASSERT_NULL(lifoBufferTest.base);
  TEST_ASSERT_NULL(lifoBufferTest.head);
  TEST_ASSERT_EQUAL(0, lifoBufferTest.size);
  TEST_ASSERT_EQUAL(LIFO_FLAGS_NULL, lifoBufferTest.flag);
}
