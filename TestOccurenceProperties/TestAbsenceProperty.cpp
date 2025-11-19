#include <map>
#include <AUnit.h>
#include <automatons/properties/occurence/AbsenceProperty/AbsenceProperty.hpp>
#include <automatons/properties/occurence/AbsenceProperty/AbsenceBeforeRProperty.hpp>
#include <automatons/properties/occurence/AbsenceProperty/AbsenceAfterQProperty.hpp>
#include <automatons/properties/occurence/AbsenceProperty/AbsenceBetweenQAndRProperty.hpp>

using namespace aunit;

class TestAbsenceProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestAbsenceProperty, AbsenceProperty_satisfied) {
  //given
  AbsenceProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_R, EVENT_S, EVENT_Q});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceProperty, AbsenceProperty_violated) {
  //given
  AbsenceProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_NONE});
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
  automaton.processEvents({EVENT_NONE, EVENT_R, EVENT_P, EVENT_NONE, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceProperty, AbsenceBeforeRProperty_satisfied_when_no_P_or_R) {
  //given
  AbsenceBeforeRProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestAbsenceProperty, AbsenceBeforeRProperty_violated) {
  //given
  AbsenceBeforeRProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_P, EVENT_R, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceProperty, AbsenceAfterQProperty_violated_when_P_after_Q) {
  //given
  AbsenceAfterQProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_Q, EVENT_P, EVENT_NONE, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceProperty, AbsenceAfterQProperty_inconclusive_when_no_P_after_Q) {
  //given
  AbsenceAfterQProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_P, EVENT_Q, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestAbsenceProperty, AbsenceAfterQProperty_inconclusive_when_no_P_or_Q) {
  //given
  AbsenceAfterQProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestAbsenceProperty, AbsenceBetweenQAndRProperty_satisfied) {
  //given
  AbsenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_Q, EVENT_NONE, EVENT_R, EVENT_NONE, EVENT_P, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceProperty, AbsenceBetweenQAndRProperty_satisfied_no_events) {
  //given
  AbsenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE});
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
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_R, EVENT_NONE, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}