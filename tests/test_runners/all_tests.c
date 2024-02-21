#include "unity_fixture.h"

static void RunAllTests(void)
{
  //RUN_TEST_GROUP(ProductionCode);
  RUN_TEST_GROUP(LifoBuffer);
  RUN_TEST_GROUP(FifoBuffer);
}

int main(int argc, const char * argv[])
{
  return UnityMain(argc, argv, RunAllTests);
}
