#include <map>
#include <AUnit.h>
#include <automatons/properties/timed/ExistenceOfPWithinTenSecondsProperty.hpp>

using namespace aunit;

class TestExistenceOfPWithinTenSecondsProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestExistenceOfPWithinTenSecondsProperty, Property_satisfied_with_P_once_every_ten_seconds) {
  //given
  ExistenceOfPWithinTenSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_NONE, EVENT_Q, EVENT_R, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_P};
  std::vector<uint32_t> timestamps = {0, 2000, 4000, 6000, 8000, 10000, 12000, 14000, 16000, 18000, 20000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceOfPWithinTenSecondsProperty, Property_violated_never_P) {
  //given
  ExistenceOfPWithinTenSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R, EVENT_NONE, EVENT_Q, EVENT_R, EVENT_NONE, EVENT_Q, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_NONE, EVENT_S};
  std::vector<uint32_t> timestamps = {0, 2000, 4000, 6000, 8000, 10000, 12000, 14000, 16000, 18000, 20000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceOfPWithinTenSecondsProperty, Property_violated_P_12_seconds_ago) {
  //given
  ExistenceOfPWithinTenSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_NONE, EVENT_Q, EVENT_R, EVENT_NONE, EVENT_Q};
  std::vector<uint32_t> timestamps = {0, 2000, 4000, 6000, 8000, 10000, 12000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceOfPWithinTenSecondsProperty, Property_violated_P_10001ms_ago) {
  //given
  ExistenceOfPWithinTenSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_NONE};
  std::vector<uint32_t> timestamps = {0, 10001};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceOfPWithinTenSecondsProperty, Property_satisfied_P_exactly_10s_ago) {
  //given
  ExistenceOfPWithinTenSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_NONE};
  std::vector<uint32_t> timestamps = {0, 9999};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}