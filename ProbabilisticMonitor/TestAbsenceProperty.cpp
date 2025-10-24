#include <map>
#include <AUnit.h>
#include "properties/untimed/AbsenceProperty/AbsenceProperty.cpp"
#include "properties/untimed/AbsenceProperty/AbsenceBeforeRProperty.cpp"
#include "properties/untimed/AbsenceProperty/AbsenceAfterQProperty.cpp"
#include "properties/untimed/AbsenceProperty/AbsenceBetweenQAndRProperty.cpp"

using namespace aunit;

class TestAbsenceProperty : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

//Tests state probabilities a basic Transition from A to B
testF(TestAbsenceProperty, AbsenceProperty_satisfied) {
  //given
  AbsenceProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.95));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.05));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

//Tests state probabilities a basic Transition from A to B
testF(TestAbsenceProperty, AbsenceProperty_violated) {
  //given
  AbsenceProperty automaton;

  //when
  automaton.processEvents("XXPXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(results[Verdict::SATISFIED] == 0.0);
  assertTrue(results[Verdict::VIOLATED] == 1.0);
  assertTrue(results[Verdict::INCONCLUSIVE] == 0.0);
}

testF(TestAbsenceProperty, AbsenceBeforeRProperty_satisfied_when_P_after_R) {
  //given
  AbsenceBeforeRProperty automaton;

  //when
  automaton.processEvents("XXRPXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.98));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.02));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceProperty, AbsenceBeforeRProperty_satisfied_when_no_P_or_R) {
  //given
  AbsenceBeforeRProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceProperty, AbsenceBeforeRProperty_violated) {
  //given
  AbsenceBeforeRProperty automaton;

  //when
  automaton.processEvents("XXPRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.02));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.98));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceProperty, AbsenceAfterQProperty_violated_when_P_after_Q) {
  //given
  AbsenceAfterQProperty automaton;

  //when
  automaton.processEvents("XXQPXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceProperty, AbsenceAfterQProperty_satisfied_when_no_P_after_Q) {
  //given
  AbsenceAfterQProperty automaton;

  //when
  automaton.processEvents("XXPQXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.96));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.04));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceProperty, AbsenceAfterQProperty_satisfied_when_no_P_or_Q) {
  //given
  AbsenceAfterQProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceProperty, AbsenceBetweenQAndRProperty_satisfied) {
  //given
  AbsenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXPXQXRXPX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.96));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.04));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceProperty, AbsenceBetweenQAndRProperty_satisfied_no_events) {
  //given
  AbsenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXXXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceProperty, AbsenceBetweenQAndRProperty_violated) {
  //given
  AbsenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQXPXRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}