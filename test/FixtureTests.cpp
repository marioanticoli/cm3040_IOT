#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "DHTWrapperTest"

int main(void)
{
  CppUnit::TextUi::TestRunner runner {};

  runner.addTest(new CppUnit::TestCaller<FixtureTests> {
    "test the addition operator",
    &DHTWrapperTest::testAddition
	});

  runner.addTest(new CppUnit::TestCaller<FixtureTests> {
    "test the logic",
    &FixtureTests::testLogic
	});

  runner.run();

  return 0;
}
