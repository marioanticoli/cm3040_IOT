#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>
#include "DHTWrapperTest.h"
// compile with 

int main(void)
{
  CppUnit::TextUi::TestRunner runner {};

  runner.addTest(new CppUnit::TestCaller<DHTWrapperTest> {
    "test the addition operator",
    &DHTWrapperTest::testAddition
	});

  runner.run();

  return 0;
}