#include "../../../State.hpp"
#include "../../../ProbTransition.hpp"
#include "../../../ProbStatemachine.hpp"

/*
This property describe the Universality of an event.
In structure english we can formulate it as:
"It is always the case that P holds"
In this implementation, the char "P" indicates that P has happened
X indicates not P
Here, we model the uncertainty in the value of the event "P"
There is a 0.01 chance for any P event to actually be not P 
*/
class UniversalityProperty : public ProbStatemachine {
  public:
    UniversalityProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> p("P", Verdict::SATISFIED);
      static State<ProbTransition> not_p("NOT_P", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&p, &p, 0.99, 'P');
      static ProbTransition t2(&p, &not_p, 0.01, 'P');
      static ProbTransition t3(&p, &not_p, 1.00, 'X');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&p);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&not_p);
    }
};