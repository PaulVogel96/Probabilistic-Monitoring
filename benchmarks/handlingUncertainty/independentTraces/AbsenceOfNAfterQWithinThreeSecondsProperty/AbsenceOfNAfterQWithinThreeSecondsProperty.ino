#include <List.hpp>
#include <State.hpp>
#include <ProbTransition.hpp>
#include <ProbStatemachine.hpp>
#include <automatons/properties/timed/AbsenceOfNAfterQWithinThreeSecondsProperty.hpp>
#include <transitions/untimed/AllRequiredEventsActiveTransition.hpp>
#include <Utils.hpp>

AbsenceOfNAfterQWithinThreeSecondsProperty automaton;
std::vector<uint8_t> events_to_process = {EVENT_Q, EVENT_S, EVENT_X, EVENT_P, EVENT_N, EVENT_Q, EVENT_NONE, EVENT_N, EVENT_R, EVENT_Y, EVENT_X};
int events_processed = 0;

void setup() {
  Serial.begin(9600);
  Serial.flush();
/* 
  //get states
  State* initial_state = automaton.getState("A");
  State* b_state = automaton.getState("B");
  State* c_state = automaton.getState("C");
  
  //remove existing transitions
  initial_state->deleteAllOutgoingTransitions();
  //create new transitions
  auto* t1_new = new AllRequiredEventsActiveTransition(initial_state, b_state, 0.8, EVENT_P);
  auto* t2_new = new AllRequiredEventsActiveTransition(initial_state, c_state, 0.2, EVENT_P); */
}

void loop() {
  if (Serial.available()) {
    if (events_processed < events_to_process.size()) {
      uint8_t event = events_to_process[events_processed];
      uint32_t timestamp = events_processed * 1000;
      automaton.changeStates(event, timestamp);
      std::map<Verdict, float> verdictProbabilities = automaton.getVerdictProbabilities();
      Serial.print(events_processed);
      Serial.print(", ");
      Serial.println(isVerdictViolated(verdictProbabilities));
      events_processed += 1;
    }
  }
}
