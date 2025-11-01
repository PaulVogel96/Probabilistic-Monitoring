#include <map>
#include <AUnit.h>
#include <automatons/properties/untimed/occurence/RecurrenceProperty/RecurrenceProperty.cpp>
#include <automatons/properties/untimed/occurence/RecurrenceProperty/RecurrenceBeforeRProperty.cpp>
#include <automatons/properties/untimed/occurence/RecurrenceProperty/RecurrenceAfterQProperty.cpp>
#include <automatons/properties/untimed/occurence/RecurrenceProperty/RecurrenceBetweenQAndRProperty.cpp>

using namespace aunit;

class TestRecurrenceProperty : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestRecurrenceProperty, RecurrenceProperty_satisfied) {
  //given
  RecurrenceProperty automaton;

  //when
  automaton.processEvents("PXPXPXP");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.99));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.01));
}

testF(TestRecurrenceProperty, RecurrenceProperty_violated) {
  //given
  RecurrenceProperty automaton;

  //when
  automaton.processEvents("XXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(results[Verdict::SATISFIED] == 0.0);
  assertTrue(results[Verdict::VIOLATED] == 0.0);
  assertTrue(results[Verdict::INCONCLUSIVE] == 1.0);
}

testF(TestRecurrenceProperty, RecurrenceBeforeRProperty_satisfied_when_P_before_R) {
  //given
  RecurrenceBeforeRProperty automaton;

  //when
  automaton.processEvents("PPRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestRecurrenceProperty, RecurrenceBeforeRProperty_inconclusive_when_no_P_or_R) {
  //given
  RecurrenceBeforeRProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestRecurrenceProperty, RecurrenceBeforeRProperty_satisfied_multiple_repetitions) {
  //given
  RecurrenceBeforeRProperty automaton;

  //when
  automaton.processEvents("PXPXPRX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.99));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.01));
}

testF(TestRecurrenceProperty, RecurrenceAfterQProperty_satisfied_just_q) {
  //given
  RecurrenceAfterQProperty automaton;

  //when
  automaton.processEvents("XXQ0XX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestRecurrenceProperty, RecurrenceAfterQProperty_satisfied) {
  //given
  RecurrenceAfterQProperty automaton;

  //when
  automaton.processEvents("PPXQXPXPXP");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.97));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.03));
}

testF(TestRecurrenceProperty, RecurrenceAfterQProperty_inconclusive_when_no_P_or_Q) {
  //given
  RecurrenceAfterQProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestRecurrenceProperty, RecurrenceBetweenQAndRProperty_satisfied) {
  //given
  RecurrenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQPRXXQRXXQPPPRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestRecurrenceProperty, RecurrenceBetweenQAndRProperty_inconclusive_no_events) {
  //given
  RecurrenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXXXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestRecurrenceProperty, RecurrenceBetweenQAndRProperty_violated) {
  //given
  RecurrenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQPXPXRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}