#include <map>
#include <AUnit.h>
#include <automatons/properties/timed/ExistenceOfPWithinTwentySecondsProperty.hpp>

using namespace aunit;

class TestExistenceOfPWithinTwentySecondsProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestExistenceOfPWithinTwentySecondsProperty, Property_satisfied_only_p) {
  //given
  ExistenceOfPWithinTwentySecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_P, EVENT_P, EVENT_P};
  std::vector<uint32_t> timestamps = {0, 20000, 40000, 60000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceOfPWithinTwentySecondsProperty, Property_satisfied_stuff_inbetween) {
  //given
  ExistenceOfPWithinTwentySecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_N, EVENT_S, EVENT_P | EVENT_X, EVENT_P, EVENT_Q};
  std::vector<uint32_t> timestamps = {0, 2000, 4000, 20000, 40000, 60000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceOfPWithinTwentySecondsProperty, Property_violated_never_p) {
  //given
  ExistenceOfPWithinTwentySecondsProperty automaton;

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

testF(TestExistenceOfPWithinTwentySecondsProperty, Property_violated_p_rarer_than_20_s) {
  //given
  ExistenceOfPWithinTwentySecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_S};
  std::vector<uint32_t> timestamps = {0, 20001};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestExistenceOfPWithinTwentySecondsProperty, Property_switches_from_satisfied_to_violated_and_back) {
  //given
  ExistenceOfPWithinTwentySecondsProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_X};
  std::vector<uint32_t> timestamps = {0, 20000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then  
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));

  //when 
  automaton.changeStates(EVENT_Q, 20001);
  std::map<Verdict, float> results2 = automaton.getVerdictProbabilities();
  
  //then
  assertTrue(approxEquals(results2[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results2[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results2[Verdict::INCONCLUSIVE], 0.0));

  //when
  automaton.changeStates(EVENT_P, 20002);
  std::map<Verdict, float> results3 = automaton.getVerdictProbabilities();

  //then  
  assertTrue(approxEquals(results3[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results3[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results3[Verdict::INCONCLUSIVE], 0.0));
} 