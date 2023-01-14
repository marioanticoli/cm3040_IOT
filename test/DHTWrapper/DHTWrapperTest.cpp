#include <cppunit/TestCase.h>

class FixtureTests : public CppUnit::TestFixture {
public:
  //void setUp(void) override {
  //}

  //void tearDown(void) override {
  //}

  void testAddition(void) {
    CPPUNIT_ASSERT(2 + 2 == 3);
    CPPUNIT_ASSERT(2 + 2 == 4);
  }

  void testLogic(void) {
    CPPUNIT_ASSERT(true == true);
    CPPUNIT_ASSERT(true == false);
  }
};

