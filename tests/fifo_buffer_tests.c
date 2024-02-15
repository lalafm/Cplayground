#include "fifo_buffer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(FifoBuffer);

//sometimes you may want to get at local data in a module.
//for example: If you plan to pass by reference, this could be useful
//however, it should often be avoided
fifo_buffer_t fifoBufferTest;

TEST_SETUP(FifoBuffer)
{
  //This is run before EACH TEST
}

TEST_TEAR_DOWN(FifoBuffer)
{
  
}

TEST(FifoBuffer, create_fifo_buffer_fail_buffer_null_1)
{
  uint32_t length = 5u;
  TEST_ASSERT_FALSE(create_fifo_buffer(NULL, length));
  // return false when fail
  //tests runs and no seg fault occurs when sending a null buffer
}

TEST(FifoBuffer, create_fifo_buffer_fail_length_0_2)
{
  uint32_t length = 0u;
  TEST_ASSERT_FALSE(create_fifo_buffer(&fifoBufferTest, length));
  // return false when fail
  //tests runs and no seg fault occurs when sending a null buffer
}

TEST(FifoBuffer, create_fifo_buffer_success_3)
{
  uint32_t length = 5u;
  create_fifo_buffer(&fifoBufferTest, length);

  //Check if correct structure was created
  TEST_ASSERT_EQUAL(length, fifoBufferTest.size);
  TEST_ASSERT_EQUAL(FIFO_FLAGS_EMPTY, fifoBufferTest.flag);
  TEST_ASSERT_EQUAL_MEMORY(fifoBufferTest.head, fifoBufferTest.base, 1);
  destroy_fifo_buffer(&fifoBufferTest);
}

TEST(FifoBuffer, create_fifo_buffer_add_word_not_full_4)
{
  //arrange
  uint8_t word[] = "casa";
  uint32_t wordSize = sizeof(word);
  uint32_t length = wordSize + 5u;
  create_fifo_buffer(&fifoBufferTest, length);
  //act
  for(uint32_t i = 0; i < wordSize; i++)
  {
    add_to_fifo_buffer(&fifoBufferTest, word[i]);
  }
  //assert
  for(uint32_t i = 0; i < wordSize; i++)
  {
    TEST_ASSERT_EQUAL(word[i], *(fifoBufferTest.tail+i));
  }
  TEST_ASSERT_EQUAL(FIFO_FLAGS_NOT_EMPTY, fifoBufferTest.flag);
  destroy_fifo_buffer(&fifoBufferTest);
}

TEST(FifoBuffer, create_fifo_buffer_add_word_full_overwrite_5)
{
  //arrange
  uint8_t word[] = "casale";
  uint32_t wordSize = sizeof(word);
  uint32_t length = wordSize-2;
  uint8_t expectedWord[5] = {'e', '\0', 's', 'a', 'l'};
  create_fifo_buffer(&fifoBufferTest, length);
  //act
  for(uint32_t i = 0; i < wordSize; i++)
  {
    add_to_fifo_buffer(&fifoBufferTest, word[i]);
  }
  //assert
  for(uint32_t i = 0; i < length; i++)
  {
    TEST_ASSERT_EQUAL(*(fifoBufferTest.base+i), expectedWord[i]);
  }
  TEST_ASSERT_EQUAL_PTR(fifoBufferTest.base+2, fifoBufferTest.tail); //oldest value is 's' at position 2
  TEST_ASSERT_EQUAL_PTR(fifoBufferTest.head, fifoBufferTest.tail);
  TEST_ASSERT_EQUAL(FIFO_FLAGS_FULL, fifoBufferTest.flag);
  destroy_fifo_buffer(&fifoBufferTest);
}

TEST(FifoBuffer, create_fifo_buffer_add_word_full_6)
{
  //arrange
  uint8_t word[] = "casa";
  uint32_t wordSize = sizeof(word);
  uint32_t length = wordSize;
  create_fifo_buffer(&fifoBufferTest, length);
  //act
  for(uint32_t i = 0; i < wordSize; i++)
  {
    add_to_fifo_buffer(&fifoBufferTest, word[i]);
  }
  //assert
  for(uint32_t i = 0; i < wordSize; i++)
  {
    TEST_ASSERT_EQUAL(word[i], *(fifoBufferTest.tail+i));
  }
  TEST_ASSERT_EQUAL(FIFO_FLAGS_FULL, fifoBufferTest.flag);
  TEST_ASSERT_EQUAL_PTR(fifoBufferTest.base, fifoBufferTest.head);
  destroy_fifo_buffer(&fifoBufferTest);
}

TEST(FifoBuffer, partial_remove_from_full_fifo_buffer_7)
{
  //arrange
  uint8_t word[] = "casamento";
  uint8_t removed[] = "casa";
  uint32_t wordSize = sizeof(word);
  uint32_t length = wordSize;
  create_fifo_buffer(&fifoBufferTest, length);
  for(uint32_t i = 0; i < wordSize; i++)
  {
    add_to_fifo_buffer(&fifoBufferTest, word[i]);
  }
  TEST_ASSERT_EQUAL_PTR(fifoBufferTest.head, fifoBufferTest.tail);
  //act and assert
  for(uint32_t i = 0; i < (sizeof(removed)-1); i++)
  {
    TEST_ASSERT_EQUAL(removed[i], remove_from_fifo_buffer(&fifoBufferTest));
  }
  TEST_ASSERT_EQUAL_PTR((fifoBufferTest.base+sizeof(removed)-1), fifoBufferTest.tail);
  TEST_ASSERT_EQUAL(FIFO_FLAGS_NOT_EMPTY, fifoBufferTest.flag);
  destroy_fifo_buffer(&fifoBufferTest);
}

TEST(FifoBuffer, remove_until_empty_from_not_full_fifo_buffer_8)
{
  //arrange
  uint8_t word[] = "casamento";
  uint8_t removed[] = "casamento";
  uint32_t wordSize = sizeof(word);
  uint32_t length = wordSize+5;
  create_fifo_buffer(&fifoBufferTest, length);
  for(uint32_t i = 0; i < wordSize; i++)
  {
    add_to_fifo_buffer(&fifoBufferTest, word[i]);
  }
  //act and assert
  for(uint32_t i = 0; i < 100; i++)
  {
    if(i < sizeof(removed))
    {
      TEST_ASSERT_EQUAL(removed[i], remove_from_fifo_buffer(&fifoBufferTest));
    }
    else
    {
      TEST_ASSERT_EQUAL(0, remove_from_fifo_buffer(&fifoBufferTest));
    }
    
  }
  TEST_ASSERT_EQUAL_PTR(fifoBufferTest.head, fifoBufferTest.tail);
  TEST_ASSERT_EQUAL_PTR((fifoBufferTest.base+wordSize), fifoBufferTest.tail);
  TEST_ASSERT_EQUAL(FIFO_FLAGS_EMPTY, fifoBufferTest.flag);
  destroy_fifo_buffer(&fifoBufferTest);
}

TEST(FifoBuffer, remove_until_empty_from_full_fifo_buffer_9)
{
  //arrange
  uint8_t word[] = "casamento";
  uint8_t removed[] = "casamento";
  uint32_t wordSize = sizeof(word);
  uint32_t length = wordSize;
  create_fifo_buffer(&fifoBufferTest, length);
  for(uint32_t i = 0; i < wordSize; i++)
  {
    add_to_fifo_buffer(&fifoBufferTest, word[i]);
  }
  TEST_ASSERT_EQUAL(FIFO_FLAGS_FULL, fifoBufferTest.flag);
  //act and assert
  for(uint32_t i = 0; i < 100; i++)
  {
    if(i < sizeof(removed))
    {
      TEST_ASSERT_EQUAL(removed[i], remove_from_fifo_buffer(&fifoBufferTest));
    }
    else
    {
      TEST_ASSERT_EQUAL(0, remove_from_fifo_buffer(&fifoBufferTest));
    }
    
  }
  TEST_ASSERT_EQUAL_PTR(fifoBufferTest.head, fifoBufferTest.tail);
  TEST_ASSERT_EQUAL_PTR(fifoBufferTest.base, fifoBufferTest.tail);
  TEST_ASSERT_EQUAL(FIFO_FLAGS_EMPTY, fifoBufferTest.flag);
  destroy_fifo_buffer(&fifoBufferTest);
}

TEST(FifoBuffer, print_fifo_buffer_casio_success_10)
{
  //arrange
  printf("From TEST(FifoBuffer, print_fifo_buffer_casio_success_10): ");
  uint8_t word[] = {'c','a','s','i','o'};
  uint32_t wordSize = sizeof(word);
  create_fifo_buffer(&fifoBufferTest, wordSize);
  for(uint32_t i = 0; i < wordSize; i++)
  {
    add_to_fifo_buffer(&fifoBufferTest, word[i]);
  }
  //act and assert
  print_fifo_buffer(&fifoBufferTest);
  // cleanup
  destroy_fifo_buffer(&fifoBufferTest);
}

TEST(FifoBuffer, print_fifo_buffer_fail_11)
{
  //arrange
  printf("From TEST(FifoBuffer, print_fifo_buffer_fail_11): ");
  create_fifo_buffer(&fifoBufferTest, 0);
  //act and assert
  print_fifo_buffer(&fifoBufferTest);
  // cleanup
  destroy_fifo_buffer(&fifoBufferTest);
}

TEST(FifoBuffer, destroy_fifo_buffer_12)
{
  //arrange
  uint8_t word[] = {'c','a','s','i','o'};
  uint32_t wordSize = sizeof(word);
  create_fifo_buffer(&fifoBufferTest, wordSize);
  for(uint32_t i = 0; i < wordSize; i++)
  {
    add_to_fifo_buffer(&fifoBufferTest, word[i]);
  }
  //act
  destroy_fifo_buffer(&fifoBufferTest);
  //assert
  TEST_ASSERT_NULL(fifoBufferTest.base);
  TEST_ASSERT_NULL(fifoBufferTest.head);
  TEST_ASSERT_NULL(fifoBufferTest.tail);
  TEST_ASSERT_EQUAL(0, fifoBufferTest.size);
  TEST_ASSERT_EQUAL(FIFO_FLAGS_NULL, fifoBufferTest.flag);
}

TEST(FifoBuffer, add_remove_add_fifo_buffer_13)
{
  //arrange
  uint8_t word[] = "whimsical";
  uint8_t expectedWord[] = "physsical";
  uint8_t removed[] = "whim";
  uint8_t add[] = "phys";
  uint32_t length = sizeof(word);
  create_fifo_buffer(&fifoBufferTest, length);
  //add
  for(uint32_t i = 0; i < sizeof(word); i++)
  {
    add_to_fifo_buffer(&fifoBufferTest, word[i]);
  }
  TEST_ASSERT_EQUAL(FIFO_FLAGS_FULL, fifoBufferTest.flag);
  //act: remove
  for(uint32_t i = 0; i < sizeof(removed)-1; i++)
  {
      TEST_ASSERT_EQUAL(removed[i], remove_from_fifo_buffer(&fifoBufferTest)); 
  }
  //act: add
  for(uint32_t i = 0; i < sizeof(add)-1; i++)
  {
      add_to_fifo_buffer(&fifoBufferTest, add[i]);
  }
  //act: assert
  for(uint32_t i = 0; i < sizeof(word); i++)
  {
      TEST_ASSERT_EQUAL(expectedWord[i], fifoBufferTest.base[i]); // or *(fifoBufferTest.base+i)
  }
  /*TEST_ASSERT_EQUAL(FIFO_FLAGS_FULL, fifoBufferTest.flag);*/
  destroy_fifo_buffer(&fifoBufferTest);
}