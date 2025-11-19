#include <map>
#include <AUnit.h>
#include <automatons/basic/ALoopBAutomaton.hpp>

using namespace aunit;

class TestProbStatemachineFunctionality : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEqual(float a, float b, float epsilon = 0.0001) {
    return fabs(a - b) < epsilon;
  }
};

//Tests that processEvents() behaves identical to multiple changeStates() calls
testF(TestProbStatemachineFunctionality, TestProcessEventsEqualsMultipleChangeStates) {
  //given
  ALoopBAutomaton automaton1;
  ALoopBAutomaton automaton2;

  //when
  automaton1.changeStates(EVENT_P);
  automaton1.changeStates(EVENT_P);
  automaton1.changeStates(EVENT_P);
  automaton2.processEvents({EVENT_P, EVENT_P, EVENT_P});
  std::map<String, float> results1 = automaton1.getStateProbabilities();
  std::map<String, float> results2 = automaton2.getStateProbabilities();

  //then
  assertTrue(results1.size() == results2.size());
  assertTrue(approxEqual(results1["A"], results2["A"]));
  assertTrue(approxEqual(results1["A"], 0.125));
  assertTrue(approxEqual(results1["B"], results2["B"]));
  assertTrue(approxEqual(results1["B"], 0.875));
}