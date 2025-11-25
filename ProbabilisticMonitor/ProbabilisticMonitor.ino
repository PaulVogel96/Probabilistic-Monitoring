#include <List.hpp>
#include <State.hpp>
#include <ProbTransition.hpp>
#include <ProbStatemachine.hpp>
#include <automatons/basic/ABCSplitAutomaton.hpp>
#include <transitions/AllRequiredEventsActiveTransition.hpp>

ABCSplitAutomaton automaton;
std::vector<uint8_t> events_to_process = {EVENT_NONE, EVENT_NONE, EVENT_P, EVENT_NONE, EVENT_NONE};
int events_processed = 0;

void setup() {
  Serial.begin(9600);
  Serial.flush();

  //get states
  State* initial_state = automaton.getState("A");
  State* b_state = automaton.getState("B");
  State* c_state = automaton.getState("C");
  
  //remove existing transitions
  initial_state->deleteAllOutgoingTransitions();
  //create new transitions
  auto* t1_new = new AllRequiredEventsActiveTransition(initial_state, b_state, 0.8, EVENT_P);
  auto* t2_new = new AllRequiredEventsActiveTransition(initial_state, c_state, 0.2, EVENT_P);
}

void loop() {
  if (Serial.available()) {
    if (events_processed < events_to_process.size()) {

      //log initial state
      if(events_processed == 0){
        std::map<Verdict, float> verdictProbabilities = automaton.getVerdictProbabilities();
        Serial.print("Start Verdict: ");
        Serial.print(verdictProbabilities[Verdict::SATISFIED]);
        Serial.print(",");
        Serial.print(verdictProbabilities[Verdict::VIOLATED]);
        Serial.print(",");
        Serial.println(verdictProbabilities[Verdict::INCONCLUSIVE]);
      }

      uint8_t event = events_to_process[events_processed];
      uint32_t timestamp = millis();

      Serial.print("Timestep: ");
      Serial.print(events_processed);
      Serial.print(", Event: ");
      Serial.print(event);
      automaton.changeStates(event, timestamp);
      automaton.setOccurenceOfAt(event, timestamp);
      events_processed += 1;

      //log state
      std::map<Verdict, float> verdictProbabilities = automaton.getVerdictProbabilities();
      Serial.print(", Verdict: ");
      Serial.print(verdictProbabilities[Verdict::SATISFIED]);
      Serial.print(", ");
      Serial.print(verdictProbabilities[Verdict::VIOLATED]);
      Serial.print(", ");
      Serial.println(verdictProbabilities[Verdict::INCONCLUSIVE]);
    }
  }
}
