#include <map>
#include <AUnit.h>
#include <automatons/basic/ALoopBAutomaton.hpp>
#include <transitions/AllRequiredEventsActiveTransition.hpp>
#include <transitions/AnyRequiredEventsActiveTransition.hpp>
#include <transitions/ExactEventsMatchTransition.hpp>

using namespace aunit;

class TestMultichannelTransitions : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEqual(float a, float b, float epsilon = 0.0001) {
    return fabs(a - b) < epsilon;
  }
};

// //Tests that processEvents() behaves identical to multiple changeStates() calls
// testF(TestMultichannelTransitions, TestProcessEventsEqualsMultipleChangeStates) {
//   //given
//   PActiveTransition transition = new PActiveTransition()

//   //when
//   automaton1.changeStates('a');
//   automaton1.changeStates('a');
//   automaton1.changeStates('a');
//   automaton2.processEvents("aaa");
//   std::map<String, float> results1 = automaton1.getStateProbabilities();
//   std::map<String, float> results2 = automaton2.getStateProbabilities();

//   //then
//   assertTrue(results1.size() == results2.size());
//   assertTrue(approxEqual(results1["A"], results2["A"]));
//   assertTrue(approxEqual(results1["A"], 0.125));
//   assertTrue(approxEqual(results1["B"], results2["B"]));
//   assertTrue(approxEqual(results1["B"], 0.875));
// }