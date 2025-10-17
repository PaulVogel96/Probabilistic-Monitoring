#include <map>
#include <AUnit.h>
#include "test/BasicABAutomaton.cpp"
#include "test/ABCSplitAutomaton.cpp"
#include "test/ALoopBAutomaton.cpp"
#include "test/DoubleSplitAutomatonWithLoop.cpp"

using namespace aunit;

class TestVerdictProbabilities : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEqual(float a, float b, float epsilon = 0.0001) {
    return fabs(a - b) < epsilon;
  }
};

//Tests verdict probabilities a basic Transition from A to B
testF(TestVerdictProbabilities, BasicABAutomaton) {
  //given
  BasicABAutomaton automaton;

  //when
  automaton.changeStates('a');
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(results[Verdict::SATISFIED] == 1.0);
  assertTrue(results[Verdict::VIOLATED] == 0.0);
  assertTrue(results[Verdict::INCONCLUSIVE] == 0.0);
}

//Tests a probabilistic transition from A to B or C
testF(TestVerdictProbabilities, ABCSplitAutomaton) {
  //given
  ABCSplitAutomaton automaton;

  //when
  automaton.changeStates('a');
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(results[Verdict::SATISFIED] == 0.5);
  assertTrue(results[Verdict::VIOLATED] == 0.5);
  assertTrue(results[Verdict::INCONCLUSIVE] == 0.0);
}

//Tests a probabilistic transition from A to B or loop back to A
testF(TestVerdictProbabilities, ALoopBAutomaton) {
  //given
  ALoopBAutomaton automaton;

  //when
  automaton.changeStates('a');
  automaton.changeStates('a');
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(results[Verdict::SATISFIED] == 0.75);
  assertTrue(results[Verdict::VIOLATED] == 0.0);
  assertTrue(results[Verdict::INCONCLUSIVE] == 0.25);
}

//Tests a Loop transition an multiple probabilitic transitions
testF(TestVerdictProbabilities, DoubleSplitAutomatonWithLoop) {
  //given
  DoubleSplitAutomatonWithLoop automaton;

  automaton.changeStates('a');
  automaton.changeStates('b');
  automaton.changeStates('c');
  automaton.changeStates('a');
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(results[Verdict::SATISFIED] == 0.52);
  assertTrue(results[Verdict::VIOLATED] == 0.28);
  assertTrue(approxEqual(results[Verdict::INCONCLUSIVE], 0.2));
}