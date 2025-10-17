#include <map>
#include <AUnit.h>
#include "test/BasicABAutomaton.cpp"
#include "test/ABCSplitAutomaton.cpp"
#include "test/ALoopBAutomaton.cpp"
#include "test/DoubleSplitAutomatonWithLoop.cpp"

using namespace aunit;

class TestStateProbabilities : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEqual(float a, float b, float epsilon = 0.0001) {
    return fabs(a - b) < epsilon;
  }
};

//Tests state probabilities a basic Transition from A to B
testF(TestStateProbabilities, BasicABAutomaton) {
  //given
  BasicABAutomaton automaton;

  //when
  automaton.changeStates('a');
  std::map<String, float> results = automaton.getStateProbabilities();

  //then
  assertTrue(results.size() == 1);
  assertTrue(results["B"] == 1.0);
}

//Tests a probabilistic transition from A to B or C
testF(TestStateProbabilities, ABCSplitAutomaton) {
  //given
  ABCSplitAutomaton automaton;

  //when
  automaton.changeStates('a');
  std::map<String, float> results = automaton.getStateProbabilities();

  //then
  assertTrue(results.size() == 2);
  assertTrue(results["B"] == 0.5);
  assertTrue(results["C"] == 0.5);
}

//Tests a probabilistic transition from A to B or loop back to A
testF(TestStateProbabilities, ALoopBAutomaton) {
  //given
  ALoopBAutomaton automaton;

  //when
  automaton.changeStates('a');
  automaton.changeStates('a');
  std::map<String, float> results = automaton.getStateProbabilities();

  //then
  assertTrue(results.size() == 2);
  assertTrue(results["A"] == 0.25);
  assertTrue(results["B"] == 0.75);
}

//Tests a Loop transition an multiple probabilitic transitions
testF(TestStateProbabilities, DoubleSplitAutomatonWithLoop) {
  //given
  DoubleSplitAutomatonWithLoop automaton;

  automaton.changeStates('a');
  automaton.changeStates('b');
  automaton.changeStates('c');
  automaton.changeStates('a');
  std::map<String, float> results = automaton.getStateProbabilities();

  //then
  assertTrue(results.size() == 7);
  assertTrue(approxEqual(results["A"], 0.04));
  assertTrue(approxEqual(results["B"], 0.06));
  assertTrue(approxEqual(results["C"], 0.10));
  assertTrue(approxEqual(results["D"], 0.12));
  assertTrue(approxEqual(results["E"], 0.18));
  assertTrue(approxEqual(results["F"], 0.40));
  assertTrue(approxEqual(results["G"], 0.10));
}
