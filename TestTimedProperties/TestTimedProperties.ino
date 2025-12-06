#include <AUnit.h>
#include <AUnitVerbose.h>

#include <List.hpp>
#include <State.hpp>
#include <ProbTransition.hpp>
#include <ProbStatemachine.hpp>


void setup() {
  Serial.begin(9600);
  Serial.flush();
}

void loop() {
  aunit::TestRunner::run();
}
