#include <map>
#include <AUnit.h>
#include <automatons/properties/untimed/occurence/ExistenceProperty/ExistenceProperty.hpp>
#include <automatons/properties/untimed/occurence/ExistenceProperty/ExistenceBeforeRProperty.hpp>
#include <automatons/properties/untimed/occurence/ExistenceProperty/ExistenceAfterQProperty.hpp>
#include <automatons/properties/untimed/occurence/ExistenceProperty/ExistenceBetweenQAndRProperty.hpp>

using namespace aunit;

class TestExistenceProperty : public TestOnce {
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

testF(TestExistenceProperty, ExistenceProperty_satisfied) {
  //given
  ExistenceProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceProperty, ExistenceProperty_never_satisfied) {
  //given
  ExistenceProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  std::vector<uint8_t> events = {EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_R, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceProperty, ExistenceBeforeRProperty_satisfied_when_no_P_or_R) {
  //given
  ExistenceBeforeRProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceProperty, ExistenceBeforeRProperty_inconclusive) {
  //given
  ExistenceBeforeRProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_NONE, EVENT_NONE, EVENT_R, EVENT_NONE, EVENT_NONE, EVENT_P};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceProperty, ExistenceAfterQProperty_satisfied_when_not_only_P_after_Q) {
  //given
  ExistenceAfterQProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_P, EVENT_NONE, EVENT_P};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  std::vector<uint8_t> events = {EVENT_P, EVENT_P, EVENT_NONE, EVENT_Q, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  std::vector<uint8_t> events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  std::vector<uint8_t> events = {
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
    EVENT_NONE, 
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
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceProperty, ExistenceBetweenQAndRProperty_satisfied_no_events) {
  //given
  ExistenceBetweenQAndRProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
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
  std::vector<uint8_t> events = {EVENT_NONE, EVENT_NONE, EVENT_Q, EVENT_NONE, EVENT_NONE, EVENT_R, EVENT_NONE, EVENT_P, EVENT_NONE};
  automaton.processEvents(events, generateIrrelevantTestingTimestamps(events.size()));
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}