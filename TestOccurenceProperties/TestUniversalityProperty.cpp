#include <map>
#include <AUnit.h>
#include <automatons/properties/occurence/UniversalityProperty/UniversalityProperty.hpp>
#include <automatons/properties/occurence/UniversalityProperty/UniversalityBeforeRProperty.hpp>
#include <automatons/properties/occurence/UniversalityProperty/UniversalityAfterQProperty.hpp>
#include <automatons/properties/occurence/UniversalityProperty/UniversalityBetweenQAndRProperty.hpp>

using namespace aunit;

class TestUniversalityProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestUniversalityProperty, UniversalityProperty_satisfied) {
  //given
  UniversalityProperty automaton;

  //when
  automaton.processEvents({EVENT_P, EVENT_P, EVENT_P, EVENT_P, EVENT_P});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityProperty_violated) {
  //given
  UniversalityProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_NONE});
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
  automaton.processEvents({EVENT_P, EVENT_P, EVENT_R, EVENT_NONE, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityBeforeRProperty_inconclusive_when_no_P_or_R) {
  //given
  UniversalityBeforeRProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestUniversalityProperty, UniversalityBeforeRProperty_violated) {
  //given
  UniversalityBeforeRProperty automaton;

  //when
  automaton.processEvents({EVENT_P, EVENT_NONE, EVENT_P, EVENT_R, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityAfterQProperty_violated_when_not_only_P_after_Q) {
  //given
  UniversalityAfterQProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_P, EVENT_NONE, EVENT_P});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityAfterQProperty_violated_when_not_P_after_Q) {
  //given
  UniversalityAfterQProperty automaton;

  //when
  automaton.processEvents({EVENT_P, EVENT_P, EVENT_NONE, EVENT_Q, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityAfterQProperty_satisfied_when_no_P_or_Q) {
  //given
  UniversalityAfterQProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityBetweenQAndRProperty_satisfied) {
  //given
  UniversalityBetweenQAndRProperty automaton;

  //when
  automaton.processEvents({
    EVENT_NONE, 
    EVENT_NONE, 
    EVENT_Q, 
    EVENT_P, 
    EVENT_R, 
    EVENT_NONE, 
    EVENT_NONE, 
    EVENT_Q, 
    EVENT_R, 
    EVENT_NONE, 
    EVENT_NONE, 
    EVENT_Q, 
    EVENT_P, 
    EVENT_P, 
    EVENT_P, 
    EVENT_R, 
    EVENT_NONE, 
    EVENT_NONE
  });
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityProperty, UniversalityBetweenQAndRProperty_satisfied_no_events) {
  //given
  UniversalityBetweenQAndRProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE});
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
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_R, EVENT_NONE, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}