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
  Results results = automaton.getResults();

  //then
  assertTrue(results.getStateProbabilities().size() == 1);
  assertTrue(results.getStateProbabilities()["B"] == 1.0);
}

//Tests a probabilistic transition from A to B or C
testF(ProbStatemachineTest, ABCSplitAutomaton) {
  //given
  ABCSplitAutomaton automaton;

  //when
  automaton.changeStates('a');
  Results results = automaton.getResults();

  //then
  assertTrue(results.getStateProbabilities().size() == 2);
  assertTrue(results.getStateProbabilities()["B"] == 0.5);
  assertTrue(results.getStateProbabilities()["C"] == 0.5);
}

//Tests a probabilistic transition from A to B or loop back to A
testF(ProbStatemachineTest, ALoopBAutomaton) {
  //given
  ALoopBAutomaton automaton;

  //when
  automaton.changeStates('a');
  automaton.changeStates('a');
  Results results = automaton.getResults();

  //then
  assertTrue(results.getStateProbabilities().size() == 2);
  assertTrue(results.getStateProbabilities()["A"] == 0.25);
  assertTrue(results.getStateProbabilities()["B"] == 0.75);
}

//Tests a Loop transition an multiple probabilitic transitions
testF(ProbStatemachineTest, DoubleSplitAutomatonWithLoop) {
  //given
  DoubleSplitAutomatonWithLoop automaton;

  automaton.changeStates('a');
  automaton.changeStates('b');
  automaton.changeStates('c');
  automaton.changeStates('a');
  Results results = automaton.getResults();
  std::map<String, float> stateProbs = results.getStateProbabilities();
  //then
  assertTrue(stateProbs.size() == 7);
  assertTrue(approxEqual(stateProbs["A"], 0.04));
  assertTrue(approxEqual(stateProbs["B"], 0.06));
  assertTrue(approxEqual(stateProbs["C"], 0.10));
  assertTrue(approxEqual(stateProbs["D"], 0.12));
  assertTrue(approxEqual(stateProbs["E"], 0.18));
  assertTrue(approxEqual(stateProbs["F"], 0.40));
  assertTrue(approxEqual(stateProbs["G"], 0.10));
}
