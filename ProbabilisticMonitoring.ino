#include <AUnit.h>
#include <AUnitVerbose.h>

#include <List.hpp>
#include "State.hpp"
#include "ProbTransition.hpp"
#include "ProbStatemachine.hpp"
#include "BasicABAutomaton.cpp"
#include "ABCSplitAutomaton.cpp"
#include "DoubleSplitAutomatonWithLoop.cpp"

// use version 1.8.2 please
// #define TEST

DoubleSplitAutomatonWithLoop automaton; 

void setup() {
  Serial.begin(9600);
  Serial.flush();
}

void loop() {
  #ifdef TEST
    aunit::TestRunner::run();
  #else
    if (Serial.available()) {
      char wort = Serial.read();
      if (wort != '\n') {
        automaton.changeStates(wort);

        Serial.println("Results: ");
        Results results = automaton.getResults();
        std::map<State<ProbTransition>*, float> probableStates = results.getProbableStates();
        for(auto it = probableStates.begin(); it != probableStates.end(); ++it){
          State<ProbTransition>* state = it ->first;
          float prob = it->second;
          Serial.print(state->getName());
          Serial.print(" with probability ");
          Serial.println(prob);
        }
        Serial.println("_________________________________");
      }
    }
  #endif
}
