#include <List.hpp>
#include <State.hpp>
#include <ProbTransition.hpp>
#include <ProbStatemachine.hpp>
#include <automatons/properties/timed/ResponseOfRAfterPWithinThreeSecondsProperty.hpp>
#include <transitions/untimed/AllRequiredEventsActiveTransition.hpp>
#include <Utils.hpp>
#include <traces/event_missing/seed2099/coupled_event_missing_seed2099_col-p_mcar1_0.hpp>

ResponseOfRAfterPWithinThreeSecondsProperty automaton;
int events_processed = 0;
std::map<Verdict, float> verdictProbabilities;

void setup() {
  Serial.begin(230400);
  Serial.flush();
  Serial.println("ts,violated");
}

void loop() {
  if (events_processed < 3603) {
    uint8_t event = pgm_read_byte(&coupled_event_missing_seed2099_col_p_mcar1_0[events_processed]);
    uint32_t timestamp = events_processed * 1000UL;
    
    automaton.changeStates(event, timestamp);

    verdictProbabilities = automaton.getVerdictProbabilities();
    Serial.println(String(events_processed) + ", " + String(isVerdictViolated(verdictProbabilities)));
    delay(20);
    events_processed += 1;
  }
}