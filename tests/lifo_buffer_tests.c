#include "lifo_buffer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(LifoBuffer);

//sometimes you may want to get at local data in a module.
//for example: If you plan to pass by reference, this could be useful
//however, it should often be avoided
lifo_buffer_t bufferTest;

TEST_SETUP(LifoBuffer)
{
  //This is run before EACH TEST
}

TEST_TEAR_DOWN(LifoBuffer)
{
  
}

TEST(LifoBuffer, create_buffer_success_1)
{
  uint32_t length = 5u;
  create_buffer(&bufferTest, length);

  //Check if correct structure was created
  TEST_ASSERT_EQUAL(length, bufferTest.size);
  TEST_ASSERT_EQUAL(LIFO_FLAGS_EMPTY, bufferTest.flag);
  TEST_ASSERT_EQUAL_MEMORY(bufferTest.head, bufferTest.base, 1);
  destroy_buffer(&bufferTest);
}

TEST(LifoBuffer, create_buffer_fail_length_0_2)
{
  uint32_t length = 0u;
  create_buffer(&bufferTest, length);

  //Check if correct structure was created
  TEST_ASSERT_EQUAL(length, bufferTest.size);
  TEST_ASSERT_EQUAL(LIFO_FLAGS_NULL, bufferTest.flag);
}

TEST(LifoBuffer, create_buffer_fail_buffer_null_3)
{
  uint32_t length = 5u;
  create_buffer(NULL, length);
  //tests runs and no seg fault occurs when sending a null buffer
}

TEST(LifoBuffer, create_buffer_add_word_full_4)
{
  char word[] = "casal";
  uint32_t length = sizeof(word);
  create_buffer(&bufferTest, length);

  // act - Add word to buffer
  for(uint32_t i = 0; i < length; i++)
  {
    add_to_buffer(&bufferTest, word[i]);
  }
  //assert
  TEST_ASSERT_EQUAL(length, bufferTest.size);
  TEST_ASSERT_EQUAL(LIFO_FLAGS_FULL, bufferTest.flag);
  TEST_ASSERT_EQUAL((length - 1), (bufferTest.head - bufferTest.base));
  for(uint32_t i = 0; i < length; i++)
  {
    TEST_ASSERT_EQUAL(*(bufferTest.base + i), word[i]);
  }
  destroy_buffer(&bufferTest);
}

TEST(LifoBuffer, create_buffer_add_word_not_full_5)
{
  char word[] = "sol";
  uint32_t wordSize = sizeof(word);
  uint32_t length = wordSize + 5u;
  create_buffer(&bufferTest, length);

  // act - Add word to buffer
  for(uint32_t i = 0; i < wordSize; i++)
  {
    add_to_buffer(&bufferTest, word[i]);
  }
  //assert
  TEST_ASSERT_EQUAL(length, bufferTest.size);
  TEST_ASSERT_EQUAL(LIFO_FLAGS_NOT_EMPTY, bufferTest.flag);
  TEST_ASSERT_EQUAL((wordSize - 1), (bufferTest.head - bufferTest.base));
  for(uint32_t i = 0; i < wordSize; i++)
  {
    TEST_ASSERT_EQUAL(*(bufferTest.base + i), word[i]);
  }
  destroy_buffer(&bufferTest);
}
/*TEST(LifoBuffer, FindFunction_WhichIsBroken_ShouldReturnTheIndexForItemsInList_WhichWillFailBecauseOurFunctionUnderTestIsBroken)
{
  // You should see this line fail in your test summary
  TEST_ASSERT_EQUAL(1, FindFunction_WhichIsBroken(34));

  // Notice the rest of these didn't get a chance to run because the line above failed.
  // Unit tests abort each test function on the first sign of trouble.
  // Then NEXT test function runs as normal.
  TEST_ASSERT_EQUAL(8, FindFunction_WhichIsBroken(8888));
}

TEST(LifoBuffer, FunctionWhichReturnsLocalVariable_ShouldReturnTheCurrentCounterValue)
{
    //This should be true because setUp set this up for us before this test
    TEST_ASSERT_EQUAL_HEX(0x5a5a, FunctionWhichReturnsLocalVariable());

    //This should be true because we can still change our answer
    Counter = 0x1234;
    TEST_ASSERT_EQUAL_HEX(0x1234, FunctionWhichReturnsLocalVariable());
}

TEST(ProductionCode, FunctionWhichReturnsLocalVariable_ShouldReturnTheCurrentCounterValueAgain)
{
    //This should be true again because setup was rerun before this test (and after we changed it to 0x1234)
    TEST_ASSERT_EQUAL_HEX(0x5a5a, FunctionWhichReturnsLocalVariable());
}

TEST(ProductionCode, FunctionWhichReturnsLocalVariable_ShouldReturnCurrentCounter_ButFailsBecauseThisTestIsActuallyFlawed)
{
    //Sometimes you get the test wrong.  When that happens, you get a failure too... and a quick look should tell
    // you what actually happened...which in this case was a failure to setup the initial condition.
    TEST_ASSERT_EQUAL_HEX(0x1234, FunctionWhichReturnsLocalVariable());
} */
