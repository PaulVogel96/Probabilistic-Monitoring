#include <map>
#include <AUnit.h>
#include <automatons/properties/untimed/order/PrecedenceProperty/PrecedenceProperty.cpp>
#include <automatons/properties/untimed/order/PrecedenceProperty/PrecedenceBeforeRProperty.cpp>
#include <automatons/properties/untimed/order/PrecedenceProperty/PrecedenceAfterQProperty.cpp>
#include <automatons/properties/untimed/order/PrecedenceProperty/PrecedenceBetweenQAndRProperty.cpp>

using namespace aunit;

class TestPrecedenceProperty : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestPrecedenceProperty, PrecedenceProperty_satisfied) {
  //given
  PrecedenceProperty automaton;

  //when
  automaton.processEvents("XXSPXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.00));
}

testF(TestPrecedenceProperty, PrecedenceProperty_violated) {
  //given
  PrecedenceProperty automaton;

  //when
  automaton.processEvents("XXPSXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.01));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.99));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestPrecedenceProperty, PrecedenceProperty_inconclusive) {
  //given
  PrecedenceProperty automaton;

  //when
  automaton.processEvents("XXXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(results[Verdict::SATISFIED] == 0.0);
  assertTrue(results[Verdict::VIOLATED] == 0.0);
  assertTrue(results[Verdict::INCONCLUSIVE] == 1.0);
}

testF(TestPrecedenceProperty, PrecedenceBeforeRProperty_satisfied_when_SP_before_R) {
  //given
  PrecedenceBeforeRProperty automaton;

  //when
  automaton.processEvents("XXSPRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestPrecedenceProperty, PrecedenceBeforeRProperty_inconclusive_when_no_SP_or_R) {
  //given
  PrecedenceBeforeRProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestPrecedenceProperty, PrecedenceBeforeRProperty_satisfied_multiple_repetitions) {
  //given
  PrecedenceBeforeRProperty automaton;

  //when
  automaton.processEvents("XSPSPRX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestPrecedenceProperty, PrecedenceBeforeRProperty_violated_no_S_before_PR) {
  //given
  PrecedenceBeforeRProperty automaton;

  //when
  automaton.processEvents("XXPRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.01));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.99));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.00));
}

testF(TestPrecedenceProperty, PrecedenceAfterQProperty_inconclusive_just_q) {
  //given
  PrecedenceAfterQProperty automaton;

  //when
  automaton.processEvents("XXQXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestPrecedenceProperty, PrecedenceAfterQProperty_satisfied) {
  //given
  PrecedenceAfterQProperty automaton;

  //when
  automaton.processEvents("PPXQSXPXPXP");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestPrecedenceProperty, PrecedenceAfterQProperty_inconclusive_when_no_P_or_Q) {
  //given
  PrecedenceAfterQProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestPrecedenceProperty, PrecedenceAfterQProperty_inconclusive_when_no_P_or_S) {
  //given
  PrecedenceAfterQProperty automaton;

  //when
  automaton.processEvents("XXXQXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestPrecedenceProperty, PrecedenceBetweenQAndRProperty_satisfied) {
  //given
  PrecedenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQSPRXXQRXXQXXSPPPRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestPrecedenceProperty, PrecedenceBetweenQAndRProperty_satisfied_no_Q_or_R) {
  //given
  PrecedenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXXXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestPrecedenceProperty, PrecedenceBetweenQAndRProperty_violated_no_S) {
  //given
  PrecedenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQPXPXRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}