#include <AUnit.h>
using namespace aunit;

class ProbStatemachineTest : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
};

testF(ProbStatemachineTest, CheckValue) {
  assertEqual(2+2, 4);
}