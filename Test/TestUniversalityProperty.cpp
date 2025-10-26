#include <map>
#include <AUnit.h>
#include <automatons/properties/untimed/UniversalityProperty/UniversalityProperty.cpp>
#include <automatons/properties/untimed/UniversalityProperty/UniversalityBeforeRProperty.cpp>
#include <automatons/properties/untimed/UniversalityProperty/UniversalityAfterQProperty.cpp>
#include <automatons/properties/untimed/UniversalityProperty/UniversalityBetweenQAndRProperty.cpp>

using namespace aunit;

class TestUniversalityProperty : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestUniversalityProperty, UniversalityProperty_satisfied) {
  //given
  UniversalityProperty automaton;

  //when
  automaton.processEvents("PPPPP");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.95));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.05));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityProperty_violated) {
  //given
  UniversalityProperty automaton;

  //when
  automaton.processEvents("XXPXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(results[Verdict::SATISFIED] == 0.0);
  assertTrue(results[Verdict::VIOLATED] == 1.0);
  assertTrue(results[Verdict::INCONCLUSIVE] == 0.0);
}

testF(TestUniversalityProperty, UniversalityBeforeRProperty_satisfied_when_P_before_R) {
  //given
  UniversalityBeforeRProperty automaton;

  //when
  automaton.processEvents("PPRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.99));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.01));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityBeforeRProperty_satisfied_when_no_P_or_R) {
  //given
  UniversalityBeforeRProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityBeforeRProperty_violated) {
  //given
  UniversalityBeforeRProperty automaton;

  //when
  automaton.processEvents("PXPRX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityAfterQProperty_violated_when_not_only_P_after_Q) {
  //given
  UniversalityAfterQProperty automaton;

  //when
  automaton.processEvents("XXQPXP");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityAfterQProperty_violated_when_not_P_after_Q) {
  //given
  UniversalityAfterQProperty automaton;

  //when
  automaton.processEvents("PPXQX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityAfterQProperty_satisfied_when_no_P_or_Q) {
  //given
  UniversalityAfterQProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityBetweenQAndRProperty_satisfied) {
  //given
  UniversalityBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQPRXXQRXXQPPPRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.98));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.02));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityBetweenQAndRProperty_satisfied_no_events) {
  //given
  UniversalityBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXXXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityBetweenQAndRProperty_violated) {
  //given
  UniversalityBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQXPXRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}