#include <List.hpp>
#include "State.hpp"
#include "ProbTransition.hpp"
#include "ProbStatemachine.hpp"

// use version 1.8.2 please

State<ProbTransition> A("A");
State<ProbTransition> B("B");
State<ProbTransition> E("E");

ProbTransition s1(&A, &B, 1.0, 'a');
ProbTransition s2(&B, &B, 1.0, 'a');
ProbTransition h1(&B, &A, 1.0, 'b');
ProbTransition h2(&A, &E, 1.0, 'b');

ProbStatemachine Automat(&A);

void setup() {
  Serial.begin(9600);
  Serial.flush();
  Serial.print("\n");
}

void loop() {
  if (Serial.available()) {
    char wort = Serial.read();
    if (wort != '\n') {
      Serial.println("Current State: ");
      State<ProbTransition>* currState = Automat.getMostLikelyCurrentState();
      Serial.println(currState->getName());
      Automat.changeStates(wort);

      Serial.println("after change: ");
      // State<ProbTransition>* currState1 = Automat.getCurrentState();
      // Serial.println(currState1->toString());
      std::map<State<ProbTransition>*, float> currentStates1 = Automat.getCurrentStates();
      for(auto it = currentStates1.begin(); it != currentStates1.end(); ++it){
        State<ProbTransition>* state = it ->first;
        float prob = it->second;
        Serial.println(state->getName());
        Serial.println(prob);
      }
    }
  }
}
