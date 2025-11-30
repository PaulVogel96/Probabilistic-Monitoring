#include <map>
#include <AUnit.h>
#include <automatons/properties/timed/RecurrenceOfPWithinTwentySecondsProperty.hpp>

using namespace aunit;

class TestRecurrenceOfPWithinTwentySecondsProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestRecurrenceOfPWithinTwentySecondsProperty, Property_inconclusive_only_p) {
  //given
  RecurrenceOfPWithinTwentySecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_P, EVENT_P, EVENT_P};
  std::vector<uint32_t> timestamps = {0, 20000, 40000, 60000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestRecurrenceOfPWithinTwentySecondsProperty, Property_inconclusive_stuff_inbetween) {
  //given
  RecurrenceOfPWithinTwentySecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_N, EVENT_S, EVENT_P | EVENT_X, EVENT_P, EVENT_Q};
  std::vector<uint32_t> timestamps = {0, 2000, 4000, 20000, 40000, 60000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestRecurrenceOfPWithinTwentySecondsProperty, Property_violated_never_p) {
  //given
  RecurrenceOfPWithinTwentySecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_Q, EVENT_R, EVENT_S};
  std::vector<uint32_t> timestamps = {0, 20000, 40000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestRecurrenceOfPWithinTwentySecondsProperty, Property_violated_p_rarer_than_20_s) {
  //given
  RecurrenceOfPWithinTwentySecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_S, EVENT_P};
  std::vector<uint32_t> timestamps = {0, 10000, 20001};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}