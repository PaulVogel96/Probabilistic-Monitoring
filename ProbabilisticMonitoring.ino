#include <AUnit.h>
#include <AUnitVerbose.h>

#include <List.hpp>
#include "State.hpp"
#include "ProbTransition.hpp"
#include "ProbStatemachine.hpp"
#include "BasicAutomaton.cpp"

// use version 1.8.2 please
//#define TEST

BasicABAutomaton automaton; 

void setup() {
  Serial.begin(9600);
  Serial.flush();
  //Serial.print("\n");
}

void loop() {
  #ifdef TEST
    aunit::TestRunner::run();
  #else
    if (Serial.available()) {
      char wort = Serial.read();
      if (wort != '\n') {
        Serial.println("Current probabilities: ");
        std::map<State<ProbTransition>*, float> currentStates = automaton.getCurrentStates();
        for(auto it = currentStates.begin(); it != currentStates.end(); ++it){
          State<ProbTransition>* state = it ->first;
          float prob = it->second;
          Serial.print(state->getName());
          Serial.print(" with probability ");
          Serial.println(prob);
        }

        Serial.println("");
        Serial.println("changing states");
        automaton.changeStates(wort);
        Serial.println("");

        Serial.println("after change: ");
        std::map<State<ProbTransition>*, float> newStates = automaton.getCurrentStates();
        for(auto it = newStates.begin(); it != newStates.end(); ++it){
          State<ProbTransition>* state = it ->first;
          float prob = it->second;
          Serial.print(state->getName());
          Serial.print(" with probability ");
          Serial.println(prob);
        }
      }
    }
  #endif
}
