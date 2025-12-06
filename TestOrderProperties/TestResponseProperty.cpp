#include <map>
#include <AUnit.h>
#include <automatons/properties/untimed/order/ResponseProperty/ResponseProperty.hpp>
#include <automatons/properties/untimed/order/ResponseProperty/ResponseBeforeRProperty.hpp>
#include <automatons/properties/untimed/order/ResponseProperty/ResponseAfterQProperty.hpp>
#include <automatons/properties/untimed/order/ResponseProperty/ResponseBetweenQAndRProperty.hpp>

using namespace aunit;

class TestResponseProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
  
  std::vector<uint32_t> generateIrrelevantTestingTimestamps(int lenght){
    std::vector<uint32_t> testingTimestamps;
    for (size_t i = 0; i < lenght; i++)
    {
      testingTimestamps.push_back(i);
    }
    return testingTimestamps;
  }
};

testF(TestResponseProperty, ResponseProperty_satisfied) {
  //given
  ResponseProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_P, EVENT_S, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseProperty, ResponseProperty_inconclusive) {
  //given
  ResponseProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestResponseProperty, ResponseBeforeRProperty_satisfied_when_SP_before_R) {
  //given
  ResponseBeforeRProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_S, EVENT_R, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseProperty, ResponseBeforeRProperty_satisfied_when_no_SP_or_R) {
  //given
  ResponseBeforeRProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_P, EVENT_S, EVENT_NONE, EVENT_P, EVENT_S, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_S, EVENT_R, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseProperty, ResponseBeforeRProperty_violated_no_S_before_PR) {
  //given
  ResponseBeforeRProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_P, EVENT_R, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseProperty, ResponseAfterQProperty_satisfied_just_q) {
  //given
  ResponseAfterQProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  const std::vector<uint8_t>& events = {EVENT_P, EVENT_P, EVENT_NONE, EVENT_Q, EVENT_P, EVENT_NONE, EVENT_P, EVENT_P, EVENT_P, EVENT_P, EVENT_S, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_P, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestResponseProperty, ResponseBetweenQAndRProperty_satisfied) {
  //given
  ResponseBetweenQAndRProperty automaton;

  //when
  const std::vector<uint8_t>& events = {
    EVENT_NONE, 
    EVENT_NONE, 
    EVENT_Q, 
    EVENT_P, 
    EVENT_S, 
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
    EVENT_P, 
    EVENT_P, 
    EVENT_P, 
    EVENT_S, 
    EVENT_R, 
    EVENT_NONE, 
    EVENT_NONE
  };
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_R, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_P, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_R, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}