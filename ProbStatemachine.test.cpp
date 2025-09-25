#include <map>
#include <AUnit.h>
#include "BasicABAutomaton.cpp"
#include "ABCSplitAutomaton.cpp"
#include "ALoopBAutomaton.cpp"
#include "DoubleSplitAutomatonWithLoop.cpp"

using namespace aunit;

class ProbStatemachineTest : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEqual(float a, float b, float epsilon = 0.0001) {
    return fabs(a - b) < epsilon;
  }
};

//Tests a basic Transition from A to B
testF(ProbStatemachineTest, BasicABAutomaton) {
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
testF(ProbStatemachineTest, ABCSplitAutomaton) {
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
testF(ProbStatemachineTest, ALoopBAutomaton) {
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
testF(ProbStatemachineTest, DoubleSplitAutomatonWithLoop) {
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
