#include <AUnit.h>
#include <AUnitVerbose.h>

#include <List.hpp>
#include "State.hpp"
#include "ProbTransition.hpp"
#include "ProbStatemachine.hpp"
#include "test/BasicABAutomaton.cpp"
#include "test/ABCSplitAutomaton.cpp"
#include "test/DoubleSplitAutomatonWithLoop.cpp"
#include "test/ALoopBAutomaton.cpp"

// use version 1.8.2 please

// comment or uncomment this flag to execute/not execute Unit Tests 
#define TEST

ALoopBAutomaton automaton; 

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);  // hardware Serial1 (pins 19 RX1, event input)
  Serial.flush();
}

void loop() {
  #ifdef TEST
    aunit::TestRunner::run();
  #else
    if (Serial1.available()) {
      char word = Serial1.read();
      if (word != '\n') {
        Serial.print("Received: ");
        Serial.println(word);
        automaton.changeStates(word);

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
