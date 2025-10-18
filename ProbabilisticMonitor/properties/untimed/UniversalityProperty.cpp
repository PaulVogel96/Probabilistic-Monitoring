#include "../../State.hpp"
#include "../../ProbTransition.hpp"
#include "../../ProbStatemachine.hpp"

/*
This property describe the absence of an event.
In structure english we can formulate it as:
"It is never the case that P holds"
In this implementation, the char "P" indicates that P has happened
R indicates that P has not happened
Here, we model the uncertainty in the value of the event
There is a 0.01 chance for any X event to actually be a P 
*/
class AbsenceProperty : public ProbStatemachine {
  public:
    AbsenceProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> not_p()"NOT_P", Verdict::SATISFIED);
      static State<ProbTransition> p("P", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&not_p, &p, 1.0, 'P');
      static ProbTransition t2(&not_p, &not_p, 0.99, 'X');
      static ProbTransition t3(&not_p, &p, 0.01, 'X');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&a);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&b);
    }
};