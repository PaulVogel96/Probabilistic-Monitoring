#include <List.hpp>
#include "State.hpp"
#include "Transition.hpp"
#include "Statemachine.hpp"

// //initializing States...
// State<Transition> s1("s1");
// State<Transition> s2("s2");
// State<Transition> s3("s3");
// State<Transition> s4("s4");
// State<Transition> s5("s5");

// //initializing Transitions of States...
// Transition t1(&s1, &s2);
// Transition t2(&s1, &s3);
// Transition t3(&s1, &s4);
// Transition t4(&s3, &s4);
// Transition t5(&s4, &s5);
// Transition t6(&s2, &s5);
// Transition t7(&s5, &s1);
// Transition t8(&s5, &s1);

State<Transition> s1("1");
State<Transition> s2("2");

Transition u(&s1, &s2);
Transition v(&s2, &s1);

//setting triggers:

//Initializing Statemachine...
Statemachine automat(&s1);

void setup() {
  Serial.begin(9600);
  Serial.flush();

  // t1.setTrigger('t');
  // t2.setTrigger('d');
  // t3.setTrigger('c');
  // t4.setTrigger('p');
  // t5.setTrigger('q');
  // t6.setTrigger('s');
  // t7.setTrigger('v');
  // t8.setTrigger('a');

  u.setTrigger('u');
  v.setTrigger('v');

  Serial.print("\n");
}

void loop() {
  if (Serial.available()) {
    char wort = Serial.read();
    if (wort != '\n') {
      Serial.print("Current State: ");
      State<Transition>* currState = automat.getCurrentState();
      Serial.println(currState->toString());

      List<Transition*> outgoingTransitions = currState -> getOutgoingTransitions();
      Transition* t = outgoingTransitions[0];
      Serial.print("Source before change: ");
      Serial.println(t->getSource()->toString());
      Serial.print("Target before change: ");
      Serial.println(t->getTarget()->toString());

      automat.changeCurrentState(wort);
      
      State<Transition>* currStatenew = automat.getCurrentState();
      Serial.print("State after transition:");
      Serial.println(currStatenew->toString());
      
      //I will now manually try to fetch the source and target states of state 1 and print them again
      List<Transition*> newList = currStatenew -> getOutgoingTransitions();
      State<Transition>* State1 = newList[0]->getTarget();

      List<Transition*> ListState1 = State1 -> getOutgoingTransitions();
      Transition* tr = ListState1[0];

      Serial.print("Source after change: ");
      Serial.println(tr->getSource()->toString());
      Serial.print("Target after change: ");
      Serial.println(tr->getTarget()->toString());

    }
  }
}
