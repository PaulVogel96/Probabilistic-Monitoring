#include <map>
#include <AUnit.h>
#include <automatons/properties/timed/probabilistic/ResponseOfQAfterPWithin5SecondsProbabilisticProperty.hpp>
#include <Utils.hpp>

using namespace aunit;

class TestResponseOfQAfterPWithin5SecondsProbabilisticProperty : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEquals(float a, float b, float epsilon = 0.001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestResponseOfQAfterPWithin5SecondsProbabilisticProperty, Example_execution) {
  //given
  ResponseOfQAfterPWithinFiveSecondsProbabilisticProperty automaton;

  //when
  std::vector<uint8_t> events = {EVENTS_MISSING, EVENT_P, EVENT_Q, EVENT_P, EVENT_NONE, EVENTS_MISSING, EVENTS_MISSING, EVENT_R, EVENT_X, EVENT_Y};
  std::vector<uint32_t> timestamps = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};

  for(int i = 0; i < events.size(); i++){
    automaton.changeStates(events[i], timestamps[i]);
    std::map<Verdict, float> results = automaton.getVerdictProbabilities();
    Serial.println(verdictMapToString(results));
  }
}