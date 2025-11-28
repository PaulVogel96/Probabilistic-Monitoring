#include <map>
#include <AUnit.h>
#include <automatons/properties/timed/AbsenceOfNAfterQWithinThreeSecondsProperty.hpp>

using namespace aunit;

class TestAbsenceOfNAfterQWithinThreeSecondsProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestAbsenceOfNAfterQWithinThreeSecondsProperty, Property_satisfied_time_passes) {
  //given
  AbsenceOfNAfterQWithinThreeSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_Q, EVENT_S, EVENT_P, EVENT_R, EVENT_X};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceOfNAfterQWithinThreeSecondsProperty, Property_satisfied_N_after_more_than_3_seconds) {
  //given
  AbsenceOfNAfterQWithinThreeSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_Q, EVENT_S, EVENT_P, EVENT_X, EVENT_N};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 3001};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceOfNAfterQWithinThreeSecondsProperty, Property_violated) {
  //given
  AbsenceOfNAfterQWithinThreeSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_Q, EVENT_S, EVENT_N, EVENT_X};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceOfNAfterQWithinThreeSecondsProperty, Property_violated_N_at_exactly_3_s) {
  //given
  AbsenceOfNAfterQWithinThreeSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_Q, EVENT_S, EVENT_X, EVENT_N};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceOfNAfterQWithinThreeSecondsProperty, Property_satisfied_longer_trace) {
  //given
  AbsenceOfNAfterQWithinThreeSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_Q, EVENT_S, EVENT_X, EVENT_P, EVENT_N, EVENT_Q, EVENT_NONE, EVENT_R, EVENT_Y, EVENT_N, EVENT_X};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestAbsenceOfNAfterQWithinThreeSecondsProperty, Property_violated_longer_trace) {
  //given
  AbsenceOfNAfterQWithinThreeSecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_Q, EVENT_S, EVENT_X, EVENT_P, EVENT_N, EVENT_Q, EVENT_NONE, EVENT_N, EVENT_R, EVENT_Y, EVENT_X};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then  
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
} 