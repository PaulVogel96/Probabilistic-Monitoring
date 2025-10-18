#include "../../../State.hpp"
#include "../../../ProbTransition.hpp"
#include "../../../ProbStatemachine.hpp"

/*
This property describe the absence of an event.
In structure english we can formulate it as:
"It is never the case that P holds"
In this implementation, the char "P" indicates that P has happened
X indicates that P has not happened
Here, we model the uncertainty in the value of the event
There is a 0.01 chance for any X event to actually be a P 
*/
class AbsenceProperty : public ProbStatemachine {
  public:
    AbsenceProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("A", Verdict::SATISFIED);
      static State<ProbTransition> p_has_happened("B", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &p_has_happened, 1.0, 'P');
      static ProbTransition t2(&initial_state, &initial_state, 0.99, 'R');
      static ProbTransition t3(&initial_state, &p_has_happened, 0.01, 'R');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&p_has_happened);
    }
};