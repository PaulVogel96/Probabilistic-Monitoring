#include <map>
#include <AUnit.h>
#include <automatons/properties/untimed/order/PrecedenceProperty/PrecedenceProperty.hpp>
#include <automatons/properties/untimed/order/PrecedenceProperty/PrecedenceBeforeRProperty.hpp>
#include <automatons/properties/untimed/order/PrecedenceProperty/PrecedenceAfterQProperty.hpp>
#include <automatons/properties/untimed/order/PrecedenceProperty/PrecedenceBetweenQAndRProperty.hpp>

using namespace aunit;

class TestPrecedenceProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestPrecedenceProperty, PrecedenceProperty_satisfied) {
  //given
  PrecedenceProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_S, EVENT_P, EVENT_NONE, EVENT_NONE});
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
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_P, EVENT_S, EVENT_NONE, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestPrecedenceProperty, PrecedenceProperty_inconclusive) {
  //given
  PrecedenceProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE});
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
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_S, EVENT_P, EVENT_R, EVENT_NONE, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestPrecedenceProperty, PrecedenceBeforeRProperty_inconclusive_when_no_SP_or_R) {
  //given
  PrecedenceBeforeRProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE});
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
  automaton.processEvents({EVENT_NONE, EVENT_S, EVENT_P, EVENT_S, EVENT_P, EVENT_R, EVENT_NONE});
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
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_P, EVENT_R, EVENT_NONE, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestPrecedenceProperty, PrecedenceAfterQProperty_inconclusive_just_q) {
  //given
  PrecedenceAfterQProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_NONE, EVENT_NONE});
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
  automaton.processEvents({EVENT_P, EVENT_P, EVENT_NONE, EVENT_Q, EVENT_S, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_P});
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
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE});
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
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_NONE, EVENT_NONE, EVENT_NONE});
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
  automaton.processEvents({
    EVENT_NONE, 
    EVENT_NONE, 
    EVENT_Q, 
    EVENT_S, 
    EVENT_P, 
    EVENT_R, 
    EVENT_NONE, 
    EVENT_NONE, 
    EVENT_Q, 
    EVENT_R, 
    EVENT_NONE, 
    EVENT_NONE, 
    EVENT_Q, 
    EVENT_NONE, 
    EVENT_NONE, 
    EVENT_S, 
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

testF(TestPrecedenceProperty, PrecedenceBetweenQAndRProperty_satisfied_no_Q_or_R) {
  //given
  PrecedenceBetweenQAndRProperty automaton;

  //when
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE});
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
  automaton.processEvents({EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_P, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_R, EVENT_NONE, EVENT_NONE});
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}