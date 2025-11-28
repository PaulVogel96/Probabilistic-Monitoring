#include <map>
#include <AUnit.h>
#include <automatons/properties/timed/ExistenceOfSAfterRWithinFourSecondsProperty.hpp>

using namespace aunit;

class TestExistenceOfSAfterRWithinFourSecondsProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestExistenceOfSAfterRWithinFourSecondsProperty, Property_satisfied) {
  //given
  ExistenceOfSAfterRWithinFourSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R, EVENT_S, EVENT_P, EVENT_P, EVENT_X};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceOfSAfterRWithinFourSecondsProperty, Property_inconclusive_before_4_seconds_with_no_S) {
  //given
  ExistenceOfSAfterRWithinFourSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R, EVENT_P};
  std::vector<uint32_t> timestamps = {0, 1000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestExistenceOfSAfterRWithinFourSecondsProperty, Property_violated) {
  //given
  ExistenceOfSAfterRWithinFourSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R, EVENT_X, EVENT_N, EVENT_X, EVENT_NONE, EVENTS_MISSING};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000, 5000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceOfSAfterRWithinFourSecondsProperty, Property_violated_S_after_4_seconds) {
  //given
  ExistenceOfSAfterRWithinFourSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R, EVENT_S};
  std::vector<uint32_t> timestamps = {0, 4001};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceOfSAfterRWithinFourSecondsProperty, Property_satisfied_longer_trace) {
  //given
  ExistenceOfSAfterRWithinFourSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R, EVENT_S, EVENT_X, EVENT_P, EVENT_N, EVENT_R, EVENT_NONE, EVENT_R, EVENT_S, EVENT_N, EVENT_X};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceOfSAfterRWithinFourSecondsProperty, Property_violated_longer_trace) {
  //given
  ExistenceOfSAfterRWithinFourSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R, EVENT_S, EVENT_X, EVENT_P, EVENT_N, EVENT_R, EVENT_Q, EVENT_NONE, EVENT_N, EVENT_Y, EVENT_X};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}