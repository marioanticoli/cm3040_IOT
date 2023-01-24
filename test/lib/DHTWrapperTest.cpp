#include <cppunit/TestCase.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>
#include "DHTWrapperTest.h"

void DHTWrapperTest::testAddition() {
  CPPUNIT_ASSERT(2 + 2 == 4);
  CPPUNIT_ASSERT(2 + 2 == 3);
}
