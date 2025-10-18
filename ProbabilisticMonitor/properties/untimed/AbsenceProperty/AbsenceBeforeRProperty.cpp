#include "../../../State.hpp"
#include "../../../ProbTransition.hpp"
#include "../../../ProbStatemachine.hpp"

/*
This property describes the absence of an event before the  
In structure english we can formulate it as:
"It is never the case that P holds before R holds"
The property is violated in two cases:
1. P happens, but R never happens
1. R happens and P happens afterwards
In this implementation: 
- the char "P" indicates that P has happened
- the char "R" indicates that R has happened
- the char "X" indicates that neither R nor P has happened
Here, we model the uncertainty in the value of the event
There is a 0.01 chance for any X event to actually be a P and
there is a 0.01 chance for any X event to actually be a R 
*/
class AbsenceBeforeRProperty : public ProbStatemachine {
  public:
    AbsenceBeforeRProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> r_has_happened("R happened", Verdict::SATISFIED);
      static State<ProbTransition> p_has_happened("P happened", Verdict::SATISFIED);
      static State<ProbTransition> r_has_happened_after_p("R happened after P", Verdict::VIOLATED);
      static State<ProbTransition> p_has_happened_after_r("P happened after R", Verdict::SATISFIED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &initial_state, 0.98, 'X');
      static ProbTransition t1(&initial_state, &r_has_happened, 0.01, 'X'); //0.01 chance that X is actually R
      static ProbTransition t1(&initial_state, &p_has_happened, 0.01, 'X'); //0.01 chance that X is actually P
      static ProbTransition t1(&initial_state, &r_has_happened, 1.0, 'R');
      static ProbTransition t1(&initial_state, &p_has_happened, 1.0, 'P');
      static ProbTransition t1(&p_has_happened, &r_has_happened_after_p, 1.0, 'R');
      static ProbTransition t1(&r_has_happened, &p_has_happened_after_r, 1.0, 'P');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&r_has_happened);
      this->addState(&p_has_happened);
      this->addState(&r_has_happened_after_p);
      this->addState(&p_has_happened_after_r);
    }
};