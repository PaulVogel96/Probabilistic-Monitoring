#include <map>
#include <AUnit.h>
#include <automatons/properties/timed/UniversalityOfSAfterRWithinThreeSecondsProperty.hpp>

using namespace aunit;

class TestUniversalityOfSAfterRWithinThreeSecondsProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestUniversalityOfSAfterRWithinThreeSecondsProperty, Property_satisfied) {
  //given
  UniversalityOfSAfterRWithinThreeSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R, EVENT_S, EVENT_P | EVENT_S, EVENT_R | EVENT_S, EVENT_X | EVENT_S, EVENT_P | EVENT_S, EVENT_S, EVENT_N};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityOfSAfterRWithinThreeSecondsProperty, Property_inconclusive) {
  //given
  UniversalityOfSAfterRWithinThreeSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R, EVENT_S};
  std::vector<uint32_t> timestamps = {0, 1000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestUniversalityOfSAfterRWithinThreeSecondsProperty, Property_violated) {
  //given
  UniversalityOfSAfterRWithinThreeSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R, EVENT_Q};
  std::vector<uint32_t> timestamps = {0, 2000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityOfSAfterRWithinThreeSecondsProperty, Property_violated_longer_trace) {
  //given
  UniversalityOfSAfterRWithinThreeSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R, EVENT_S, EVENT_P, EVENT_S, EVENT_X, EVENT_S, EVENT_S};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000, 5000, 6000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}