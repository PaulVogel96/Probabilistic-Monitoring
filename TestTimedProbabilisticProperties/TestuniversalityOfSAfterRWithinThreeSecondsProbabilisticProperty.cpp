#include <map>
#include <AUnit.h>
#include <automatons/properties/timed/probabilistic/UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty.hpp>

using namespace aunit;

class TestUniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestUniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty, Property_satisfied) {
  //given
  UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R | EVENT_S, EVENT_S, EVENT_P | EVENT_S, EVENT_R | EVENT_S, EVENT_X | EVENT_S, EVENT_P | EVENT_S, EVENT_S, EVENT_N};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty, Property_inconclusive) {
  //given
  UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R | EVENT_S, EVENT_S};
  std::vector<uint32_t> timestamps = {0, 1000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestUniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty, Property_violated) {
  //given
  UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty automaton;

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

testF(TestUniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty, Property_violated_no_s_at_time_r) {
  //given
  UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R};
  std::vector<uint32_t> timestamps = {0};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty, Property_inconclusive_s_at_time_r) {
  //given
  UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R | EVENT_S};
  std::vector<uint32_t> timestamps = {0};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestUniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty, Property_violated_but_switches_back_to_satisfied_after_window_over) {
  //given
  UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R, EVENT_S, EVENT_P, EVENT_S, EVENT_X, EVENT_S, EVENT_S};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000, 5000, 6000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty, Property_switches_from_satisfied_to_violated_and_back) {
  //given
  UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_R, EVENT_S, EVENT_N};
  std::vector<uint32_t> timestamps = {0, 2000, 4000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then  
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));

  //when 
  std::vector<uint8_t> events2 = {EVENT_R, EVENT_X};
  std::vector<uint32_t> timestamps2 = {5000, 6000};
  automaton.processEvents(events2, timestamps2);
  std::map<Verdict, float> results2 = automaton.getVerdictProbabilities();
  
  //then
  assertTrue(approxEquals(results2[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results2[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results2[Verdict::INCONCLUSIVE], 0.0));

  //when
  std::vector<uint8_t> events3 = {EVENT_R | EVENT_S, EVENT_S, EVENT_P};
  std::vector<uint32_t> timestamps3 = {7000, 8000, 11000};
  automaton.processEvents(events3, timestamps3);
  std::map<Verdict, float> results3 = automaton.getVerdictProbabilities();

  //then  
  assertTrue(approxEquals(results3[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results3[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results3[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty, Property_violated_when_r_occurs_without_s_after_window) {
  //given

  UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty automaton;

  //when
  automaton.processEvents(
    { EVENT_R | EVENT_S, EVENT_S, EVENT_S},
    { 0, 1000, 2000 }
  );

  //then
  auto results1 = automaton.getVerdictProbabilities();
  assertTrue(approxEquals(results1[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results1[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results1[Verdict::INCONCLUSIVE], 0.0));

  //when
  automaton.processEvents({ EVENT_R }, { 3000 });

  //then
  auto results2 = automaton.getVerdictProbabilities();
  assertTrue(approxEquals(results2[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results2[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results2[Verdict::INCONCLUSIVE], 0.0));
}