#include <List.hpp>
#include <State.hpp>
#include <ProbTransition.hpp>
#include <ProbStatemachine.hpp>
#include <automatons/properties/timed/AbsenceOfNAfterQWithinThreeSecondsProperty.hpp>
#include <transitions/untimed/AllRequiredEventsActiveTransition.hpp>
#include <Utils.hpp>
#include <independent_trace_baseline.hpp>

AbsenceOfNAfterQWithinThreeSecondsProperty automaton;
int events_processed = 0;
std::map<Verdict, float> verdictProbabilities;

void setup() {
  Serial.begin(9600);
  Serial.flush();
}

void loop() {
  if (events_processed < 3603) {
    uint8_t event = pgm_read_byte(&independent_trace_baseline[events_processed]);
    uint32_t timestamp = events_processed * 1000UL;
    
    automaton.changeStates(event, timestamp);

    verdictProbabilities = automaton.getVerdictProbabilities();
    Serial.print(events_processed);
    Serial.print(", ");
    Serial.println(isVerdictViolated(verdictProbabilities));

    events_processed += 1;
  }
}
