#include <AUnit.h>
#include <AUnitVerbose.h>

#include <List.hpp>
#include "State.hpp"
#include "ProbTransition.hpp"
#include "ProbStatemachine.hpp"
#include "BasicABAutomaton.cpp"
#include "ABCSplitAutomaton.cpp"
#include "DoubleSplitAutomatonWithLoop.cpp"
#include "ALoopBAutomaton.cpp"

// use version 1.8.2 please

// comment or uncomment this flag to execute/not execute Unit Tests 
#define TEST

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
        std::map<Verdict, float> verdictProbabilities = automaton.getVerdictProbabilities();

        Serial.println("Verdict:");
        Serial.print("Inconclusive: ");
        Serial.println(verdictProbabilities[Verdict::INCONCLUSIVE]);
        Serial.print("Satisfied: ");
        Serial.println(verdictProbabilities[Verdict::SATISFIED]);
        Serial.print("Violated: ");
        Serial.println(verdictProbabilities[Verdict::VIOLATED]);
        Serial.println("_________________________________");
      }
    }
  #endif
}
