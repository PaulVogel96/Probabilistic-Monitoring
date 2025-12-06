#include <map>
#include <AUnit.h>
#include <automatons/properties/untimed/order/UntilProperty/UntilProperty.hpp>
#include <automatons/properties/untimed/order/UntilProperty/UntilBeforeRProperty.hpp>
#include <automatons/properties/untimed/order/UntilProperty/UntilAfterQProperty.hpp>
#include <automatons/properties/untimed/order/UntilProperty/UntilBetweenQAndRProperty.hpp>

using namespace aunit;

class TestUntilProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.01) {
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

testF(TestUntilProperty, UntilProperty_satisfied) {
  //given
  UntilProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_P, EVENT_S, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilProperty_inconclusive) {
  //given
  UntilProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_P, EVENT_P, EVENT_P, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilBeforeRProperty_satisfied_when_PS_before_R) {
  //given
  UntilBeforeRProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_P, EVENT_P, EVENT_S, EVENT_R, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilBeforeRProperty_violated_when_no_SP_or_R) {
  //given
  UntilBeforeRProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilBeforeRProperty_satisfied_multiple_repetitions) {
  //given
  UntilBeforeRProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_P, EVENT_P, EVENT_P, EVENT_P, EVENT_P, EVENT_S, EVENT_R, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilAfterQProperty_violated_just_q) {
  //given
  UntilAfterQProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilAfterQProperty_satisfied) {
  //given
  UntilAfterQProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_P, EVENT_P, EVENT_NONE, EVENT_Q, EVENT_P, EVENT_P, EVENT_P, EVENT_P, EVENT_P, EVENT_S, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilAfterQProperty_satisfied_when_no_P_or_S_or_Q) {
  //given
  UntilAfterQProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilAfterQProperty_inconclusive_when_no_S) {
  //given
  UntilAfterQProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_P, EVENT_P, EVENT_P, EVENT_P, EVENT_P, EVENT_P};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestUntilProperty, UntilBetweenQAndRProperty_satisfied) {
  //given
  UntilBetweenQAndRProperty automaton;

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
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilBetweenQAndRProperty_satisfied_no_Q) {
  //given
  UntilBetweenQAndRProperty automaton;

  //when
  const std::vector<uint8_t>& events = {
    EVENT_NONE, 
    EVENT_NONE, 
    EVENT_NONE, 
    EVENT_R, 
    EVENT_NONE, 
    EVENT_NONE, 
    EVENT_NONE, 
    EVENT_S, 
    EVENT_P, 
    EVENT_S, 
    EVENT_P, 
    EVENT_S, 
    EVENT_P, 
    EVENT_S, 
    EVENT_NONE
  };
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilBetweenQAndRProperty_violated_P_interrupted_before_S) {
  //given
  UntilBetweenQAndRProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_P, EVENT_P, EVENT_NONE, EVENT_S, EVENT_R, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}


testF(TestUntilProperty, UntilBetweenQAndRProperty_satisfied_no_S) {
  //given
  UntilBetweenQAndRProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_P, EVENT_P, EVENT_P, EVENT_P, EVENT_R, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}