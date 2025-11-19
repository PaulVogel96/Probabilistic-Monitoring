#include <List.hpp>
#include <State.hpp>
#include <ProbTransition.hpp>
#include <ProbStatemachine.hpp>
#include <automatons/basic/BasicABAutomaton.hpp>
#include <automatons/basic/ABCSplitAutomaton.hpp>
#include <automatons/basic/DoubleSplitAutomatonWithLoop.hpp>
#include <automatons/basic/ALoopBAutomaton.hpp>

BasicABAutomaton automaton; 

void setup() {
  Serial.begin(9600);
  Serial.flush();
}

void loop() {
  if (Serial.available()) {
    char word = Serial.read();
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
}
