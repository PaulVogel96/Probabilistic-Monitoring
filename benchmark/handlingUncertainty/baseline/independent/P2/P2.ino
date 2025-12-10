#include <List.hpp>
#include <State.hpp>
#include <ProbTransition.hpp>
#include <ProbStatemachine.hpp>
#include <automatons/properties/timed/ExistenceOfSAfterRWithinFourSecondsProperty.hpp>
#include <transitions/untimed/AllRequiredEventsActiveTransition.hpp>
#include <Utils.hpp>
#include <traces/baseline/independent_baseline.hpp>

ExistenceOfSAfterRWithinFourSecondsProperty automaton;
int events_processed = 0;
std::map<Verdict, float> verdictProbabilities;

void setup() {
  Serial.begin(230400);
  Serial.flush();
  Serial.println("ts,violated");
}

void loop() {
  if (events_processed < 3603) {
    uint8_t event = pgm_read_byte(&independent_baseline[events_processed]);
    uint32_t timestamp = events_processed * 1000UL;
    
    automaton.changeStates(event, timestamp);

    verdictProbabilities = automaton.getVerdictProbabilities();
    Serial.println(String(events_processed) + ", " + String(isVerdictViolated(verdictProbabilities)));
    delay(2);

    events_processed += 1;
  }
}
