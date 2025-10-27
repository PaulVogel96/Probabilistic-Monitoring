#include <map>
#include <AUnit.h>
#include <automatons/properties/untimed/ExistenceProperty/ExistenceProperty.cpp>
#include <automatons/properties/untimed/ExistenceProperty/ExistenceBeforeRProperty.cpp>
#include <automatons/properties/untimed/ExistenceProperty/ExistenceAfterQProperty.cpp>
#include <automatons/properties/untimed/ExistenceProperty/ExistenceBetweenQAndRProperty.cpp>

using namespace aunit;

class TestExistenceProperty : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestExistenceProperty, ExistenceProperty_satisfied) {
  //given
  ExistenceProperty automaton;

  //when
  automaton.processEvents("XXXXXXPXXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.99));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.01));
}

testF(TestExistenceProperty, ExistenceProperty_never_satisfied) {
  //given
  ExistenceProperty automaton;

  //when
  automaton.processEvents("XXXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(results[Verdict::SATISFIED] == 0.0);
  assertTrue(results[Verdict::VIOLATED] == 0.0);
  assertTrue(results[Verdict::INCONCLUSIVE] == 1.0);
}

testF(TestExistenceProperty, ExistenceBeforeRProperty_satisfied_when_P_before_R) {
  //given
  ExistenceBeforeRProperty automaton;

  //when
  automaton.processEvents("XPXRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.99));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.01));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceProperty, ExistenceBeforeRProperty_satisfied_when_no_P_or_R) {
  //given
  ExistenceBeforeRProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceProperty, ExistenceBeforeRProperty_violated) {
  //given
  ExistenceBeforeRProperty automaton;

  //when
  automaton.processEvents("XXRXXP");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceProperty, ExistenceAfterQProperty_satisfied_when_not_only_P_after_Q) {
  //given
  ExistenceAfterQProperty automaton;

  //when
  automaton.processEvents("XXQPXP");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceProperty, ExistenceAfterQProperty_violated_when_not_P_after_Q) {
  //given
  ExistenceAfterQProperty automaton;

  //when
  automaton.processEvents("PPXQXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceProperty, ExistenceAfterQProperty_satisfied_when_no_P_or_Q) {
  //given
  ExistenceAfterQProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceProperty, ExistenceBetweenQAndRProperty_satisfied) {
  //given
  ExistenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQPRXXQRXXQXPPPRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceProperty, ExistenceBetweenQAndRProperty_satisfied_no_events) {
  //given
  ExistenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXXXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceProperty, ExistenceBetweenQAndRProperty_violated) {
  //given
  ExistenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQXXRXPX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}