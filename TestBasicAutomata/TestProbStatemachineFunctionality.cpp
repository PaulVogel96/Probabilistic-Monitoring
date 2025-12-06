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

testF(TestProbStatemachineFunctionality, TestProcessEventsEqualsMultipleChangeStates) {
  //given
  ALoopBAutomaton automaton1;
  ALoopBAutomaton automaton2;

  //when
  automaton1.changeStates(EVENT_P, 0);
  automaton1.changeStates(EVENT_P, 1);
  automaton1.changeStates(EVENT_P, 2);
  automaton2.processEvents({EVENT_P, EVENT_P, EVENT_P}, { 1, 2, 3});
  std::map<String, float> results1 = automaton1.getStateProbabilities();
  std::map<String, float> results2 = automaton2.getStateProbabilities();

  //then
  assertTrue(results1.size() == results2.size());
  assertTrue(approxEqual(results1["A"], results2["A"]));
  assertTrue(approxEqual(results1["A"], 0.125));
  assertTrue(approxEqual(results1["B"], results2["B"]));
  assertTrue(approxEqual(results1["B"], 0.875));
}

testF(TestProbStatemachineFunctionality, TestRecordEventTimestamps_basic) {
  //given
  ALoopBAutomaton automaton;
  
  //when
  automaton.setOccurenceOfAt(EVENT_P, 0);
  automaton.setOccurenceOfAt(EVENT_Q, 1);
  automaton.setOccurenceOfAt(EVENT_R, 2);
  automaton.setOccurenceOfAt(EVENT_S, 3);

  //then
  assertTrue(automaton.getLastOccurenceOf(EVENT_P) == 0);
  assertTrue(automaton.getLastOccurenceOf(EVENT_Q) == 1);
  assertTrue(automaton.getLastOccurenceOf(EVENT_R) == 2);
  assertTrue(automaton.getLastOccurenceOf(EVENT_S) == 3);
}

testF(TestProbStatemachineFunctionality, TestRecordEventTimestamps_advanced) {
  //given
  ALoopBAutomaton automaton;
  
  //when
  automaton.setOccurenceOfAt(EVENT_P, 0);
  automaton.setOccurenceOfAt(EVENT_Q, 1);
  automaton.setOccurenceOfAt(EVENT_R, 2);
  automaton.setOccurenceOfAt(EVENT_P | EVENT_Q | EVENT_R | EVENT_S, 3);

  //then
  assertTrue(automaton.getLastOccurenceOf(EVENT_P) == 3);
  assertTrue(automaton.getLastOccurenceOf(EVENT_Q) == 3);
  assertTrue(automaton.getLastOccurenceOf(EVENT_R) == 3);
  assertTrue(automaton.getLastOccurenceOf(EVENT_S) == 3);
}

testF(TestProbStatemachineFunctionality, TestRecordEventTimestamps_mixed) {
  //given
  ALoopBAutomaton automaton;
  
  //when
  automaton.setOccurenceOfAt(EVENT_P, 0);
  automaton.setOccurenceOfAt(EVENT_Q | EVENT_P, 1);
  automaton.setOccurenceOfAt(EVENT_R, 2);
  automaton.setOccurenceOfAt(EVENT_R | EVENT_S, 3);

  //then
  assertTrue(automaton.getLastOccurenceOf(EVENT_P) == 1);
  assertTrue(automaton.getLastOccurenceOf(EVENT_Q) == 1);
  assertTrue(automaton.getLastOccurenceOf(EVENT_R) == 3);
  assertTrue(automaton.getLastOccurenceOf(EVENT_S) == 3);
}


testF(TestProbStatemachineFunctionality, TestRecordEventTimestamps_nothing_set) {
  //given
  ALoopBAutomaton automaton;
  
  //when
  //then
  assertTrue(automaton.getLastOccurenceOf(EVENT_P) == NULL);
  assertTrue(automaton.getLastOccurenceOf(EVENT_P) == NULL);
  assertTrue(automaton.getLastOccurenceOf(EVENT_P) == NULL);
  assertTrue(automaton.getLastOccurenceOf(EVENT_P) == NULL);
}