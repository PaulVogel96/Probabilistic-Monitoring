#include <map>
#include <AUnit.h>
#include <automatons/properties/timed/probabilistic/ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty.hpp>

using namespace aunit;

class TestResponseOfRAfterPWithinThreeSecondsProbabilisticProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestResponseOfRAfterPWithinThreeSecondsProbabilisticProperty, Property_satisfied) {
  //given
  ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_S, EVENT_P, EVENT_R, EVENT_X, EVENT_P, EVENT_S, EVENT_R};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseOfRAfterPWithinThreeSecondsProbabilisticProperty, Property_inconclusive) {
  //given
  ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P};
  std::vector<uint32_t> timestamps = {0};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 1.0));
}

testF(TestResponseOfRAfterPWithinThreeSecondsProbabilisticProperty, Property_violated) {
  //given
  ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_N};
  std::vector<uint32_t> timestamps = {0, 4000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseOfRAfterPWithinThreeSecondsProbabilisticProperty, Property_violated_longer_trace) {
  //given
  ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_S, EVENT_P, EVENT_Q, EVENT_X, EVENT_S, EVENT_S};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000, 5000, 6000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestResponseOfRAfterPWithinThreeSecondsProbabilisticProperty, Property_switches_from_satisfied_to_violated_and_back) {
  //given
  ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENT_P, EVENT_R};
  std::vector<uint32_t> timestamps = {0, 3000};
  automaton.processEvents(events, timestamps);
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then  
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));

  //when 
  std::vector<uint8_t> events2 = {EVENT_P, EVENT_X};
  std::vector<uint32_t> timestamps2 = {4000, 8000};
  automaton.processEvents(events2, timestamps2);
  std::map<Verdict, float> results2 = automaton.getVerdictProbabilities();
  
  //then
  assertTrue(approxEquals(results2[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results2[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results2[Verdict::INCONCLUSIVE], 0.0));

  //when
  std::vector<uint8_t> events3 = {EVENT_P, EVENT_R};
  std::vector<uint32_t> timestamps3 = {9000, 12000};
  automaton.processEvents(events3, timestamps3);
  std::map<Verdict, float> results3 = automaton.getVerdictProbabilities();

  //then  
  assertTrue(approxEquals(results3[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results3[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results3[Verdict::INCONCLUSIVE], 0.0));
} 