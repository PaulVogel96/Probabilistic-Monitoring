#include <AUnit.h>
#include "BasicABAutomaton.cpp"
#include "ABCSplitAutomaton.cpp"
using namespace aunit;

class ProbStatemachineTest : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
};

testF(ProbStatemachineTest, BasicABAutomaton) {
  //given
  BasicABAutomaton automaton;

  //when
  automaton.changeStates('a');
  Results results = automaton.getResults();

  //then
  assertTrue(results.getProbableStates().size() == 1);
}

testF(ProbStatemachineTest, ABCSplitAutomaton) {
  //given
  ABCSplitAutomaton automaton;

  //when
  automaton.changeStates('a');
  Results results = automaton.getResults();

  //then
  assertTrue(results.getProbableStates().size() == 2);
}