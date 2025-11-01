#include <map>
#include <AUnit.h>
#include <automatons/properties/untimed/order/ResponseProperty/ResponseProperty.cpp>
#include <automatons/properties/untimed/order/ResponseProperty/ResponseBeforeRProperty.cpp>
#include <automatons/properties/untimed/order/ResponseProperty/ResponseAfterQProperty.cpp>
#include <automatons/properties/untimed/order/ResponseProperty/ResponseBetweenQAndRProperty.cpp>

using namespace aunit;

class TestResponseProperty : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestResponseProperty, ResponseProperty_satisfied) {
  //given
  ResponseProperty automaton;

  //when
  automaton.processEvents("XXPSXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.00));
}

testF(TestResponseProperty, ResponseProperty_inconclusive) {
  //given
  ResponseProperty automaton;

  //when
  automaton.processEvents("XXXPXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.01));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.99));
}

testF(TestResponseProperty, ResponseBeforeRProperty_satisfied_when_SP_before_R) {
  //given
  ResponseBeforeRProperty automaton;

  //when
  automaton.processEvents("XXPXSRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseProperty, ResponseBeforeRProperty_satisfied_when_no_SP_or_R) {
  //given
  ResponseBeforeRProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseProperty, ResponseBeforeRProperty_satisfied_multiple_repetitions) {
  //given
  ResponseBeforeRProperty automaton;

  //when
  automaton.processEvents("XPSXPSXPXSRX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseProperty, ResponseBeforeRProperty_violated_no_S_before_PR) {
  //given
  ResponseBeforeRProperty automaton;

  //when
  automaton.processEvents("XXPRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.01));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.99));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.00));
}

testF(TestResponseProperty, ResponseAfterQProperty_satisfied_just_q) {
  //given
  ResponseAfterQProperty automaton;

  //when
  automaton.processEvents("XXQXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseProperty, ResponseAfterQProperty_satisfied) {
  //given
  ResponseAfterQProperty automaton;

  //when
  automaton.processEvents("PPXQPXPPPPSXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseProperty, ResponseAfterQProperty_satisfied_when_no_P_or_Q) {
  //given
  ResponseAfterQProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseProperty, ResponseAfterQProperty_inconclusive_when_no_S) {
  //given
  ResponseAfterQProperty automaton;

  //when
  automaton.processEvents("XXXQPXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.01));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.99));
}

testF(TestResponseProperty, ResponseBetweenQAndRProperty_satisfied) {
  //given
  ResponseBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQPSRXXQRXXQXXPPPSRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseProperty, ResponseBetweenQAndRProperty_satisfied_no_Q_or_R) {
  //given
  ResponseBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXXXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseProperty, ResponseBetweenQAndRProperty_satisfied_no_Q) {
  //given
  ResponseBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXXRXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseProperty, ResponseBetweenQAndRProperty_violated_no_S) {
  //given
  ResponseBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQPXPXRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}