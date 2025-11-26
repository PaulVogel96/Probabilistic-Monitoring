#include <map>
#include <AUnit.h>
#include <automatons/properties/untimed/occurence/RecurrenceProperty/RecurrenceProperty.hpp>
#include <automatons/properties/untimed/occurence/RecurrenceProperty/RecurrenceBeforeRProperty.hpp>
#include <automatons/properties/untimed/occurence/RecurrenceProperty/RecurrenceAfterQProperty.hpp>
#include <automatons/properties/untimed/occurence/RecurrenceProperty/RecurrenceBetweenQAndRProperty.hpp>

using namespace aunit;

class TestRecurrenceProperty : public TestOnce {
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

testF(TestRecurrenceProperty, RecurrenceProperty_satisfied) {
  //given
  RecurrenceProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_P, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_P};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.00));
}

testF(TestRecurrenceProperty, RecurrenceProperty_violated) {
  //given
  RecurrenceProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(results[Verdict::SATISFIED] == 0.0);
  assertTrue(results[Verdict::VIOLATED] == 1.0);
  assertTrue(results[Verdict::INCONCLUSIVE] == 0.0);
}

testF(TestRecurrenceProperty, RecurrenceBeforeRProperty_satisfied_when_P_before_R) {
  //given
  RecurrenceBeforeRProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_P, EVENT_P, EVENT_R, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestRecurrenceProperty, RecurrenceBeforeRProperty_inconclusive_when_no_P_or_R) {
  //given
  RecurrenceBeforeRProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  const std::vector<uint8_t>& events = {EVENT_P, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_P, EVENT_R, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestRecurrenceProperty, RecurrenceAfterQProperty_inconclusive_just_q) {
  //given
  RecurrenceAfterQProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestRecurrenceProperty, RecurrenceAfterQProperty_satisfied) {
  //given
  RecurrenceAfterQProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_P, EVENT_P, EVENT_NONE, EVENT_Q, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_P};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestRecurrenceProperty, RecurrenceAfterQProperty_inconclusive_when_no_P_or_Q) {
  //given
  RecurrenceAfterQProperty automaton;

  //when
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  const std::vector<uint8_t>& events = {
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
  };
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  const std::vector<uint8_t>& events = {EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_P, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_R, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}