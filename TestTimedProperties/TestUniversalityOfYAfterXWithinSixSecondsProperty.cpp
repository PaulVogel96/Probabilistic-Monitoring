#include <map>
#include <AUnit.h>
#include <automatons/properties/timed/UniversalityOfYAfterXWithinSixSecondsProperty.hpp>

using namespace aunit;

class TestUniversalityOfYAfterXWithinSixSecondsProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestUniversalityOfYAfterXWithinSixSecondsProperty, Property_satisfied_time_passes) {
  //given
  UniversalityOfYAfterXWithinSixSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_X, EVENT_Y, EVENT_P};
  std::vector<uint32_t> timestamps = {0, 3000, 6001};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityOfYAfterXWithinSixSecondsProperty, Property_satisfied_other_events_can_also_happen) {
  //given
  UniversalityOfYAfterXWithinSixSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_X, EVENT_Y | EVENT_P, EVENT_Y | EVENT_Q, EVENT_Y | EVENT_R, EVENT_X};
  std::vector<uint32_t> timestamps = {0, 2000, 4000, 6000, 6001};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityOfYAfterXWithinSixSecondsProperty, Property_violated) {
  //given
  UniversalityOfYAfterXWithinSixSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_X, EVENT_Y, EVENT_N, EVENT_Y};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityOfYAfterXWithinSixSecondsProperty, Property_satisfied_nothing_happens_within_6s) {
  //given
  UniversalityOfYAfterXWithinSixSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_X, EVENT_Y};
  std::vector<uint32_t> timestamps = {0, 6001};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityOfYAfterXWithinSixSecondsProperty, Property_satisfied_longer_trace) {
  //given
  UniversalityOfYAfterXWithinSixSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_X, EVENT_Y, EVENT_Y | EVENT_Q, EVENT_Y, EVENT_N, EVENT_X, EVENT_Y | EVENT_P, EVENT_Y, EVENT_Y, EVENT_N, EVENT_X, EVENT_Y, EVENT_Y, EVENT_Y};
  std::vector<uint32_t> timestamps = {0, 2000, 4000, 6000, 8000, 10000, 12000, 14000, 16000, 18000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityOfYAfterXWithinSixSecondsProperty, Property_violated_longer_trace) {
  //given
  UniversalityOfYAfterXWithinSixSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_X, EVENT_Y, EVENT_Y, EVENT_P, EVENT_Y, EVENT_Y, EVENT_NONE, EVENT_N, EVENT_R, EVENT_Y};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityOfYAfterXWithinSixSecondsProperty, Property_switches_from_satisfied_to_violated_and_back) {
  //given
  UniversalityOfYAfterXWithinSixSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_X, EVENT_Y | EVENT_S, EVENT_N};
  std::vector<uint32_t> timestamps = {0, 3000, 7000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then  
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));

  //when 
  std::vector<uint8_t> events2 = {EVENT_X, EVENT_S};
  std::vector<uint32_t> timestamps2 = {8000, 9000};
  automaton.processEvents(events2, timestamps2);
  std::map<Verdict, float> results2 = automaton.getVerdictProbabilities();
  
  //then
  assertTrue(approxEquals(results2[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results2[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results2[Verdict::INCONCLUSIVE], 0.0));

  //when
  std::vector<uint8_t> events3 = {EVENT_X, EVENT_Y | EVENT_S, EVENT_N};
  std::vector<uint32_t> timestamps3 = {10000, 11000, 17000};
  automaton.processEvents(events3, timestamps3);
  std::map<Verdict, float> results3 = automaton.getVerdictProbabilities();

  //then  
  assertTrue(approxEquals(results3[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results3[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results3[Verdict::INCONCLUSIVE], 0.0));
} 