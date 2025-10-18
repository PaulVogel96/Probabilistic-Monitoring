#include "../../State.hpp"
#include "../../ProbTransition.hpp"
#include "../../ProbStatemachine.hpp"

/*
This property describe the absence of an event 
In structure english we can formulate it as:
"It is never the case that P holds after Q holds and"
The property is violated when:
1. Q happens and P happens afterwards
In this implementation: 
- the char "P" indicates that P has happened
- the char "Q" indicates that Q has happened
- the char "X" indicates that neither R nor P has happened
Here, we model the uncertainty in the value of the event
There is a 0.01 chance for any X event to actually be a P and
there is a 0.01 chance for any X event to actually be a Q 
*/
class AbsenceBetweenQAndRProperty : public ProbStatemachine {
  public:
    AbsenceBetweenQAndRProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::SATISFIED);
      static State<ProbTransition> p_happened_after_q("P happened after Q", Verdict::SATISFIED);
      static State<ProbTransition> r_happened_after_q_and_p("R happened after Q and P", Verdict::VIOLATED);


      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &initial_state, 0.98, 'X');
      static ProbTransition t1(&initial_state, &initial_state, 0.01, 'X'); //0.01 chance that X is actually P (P can happen before Q)
      static ProbTransition t1(&initial_state, &q_happened, 0.01, 'X'); //0.01 chance that X is actually Q
      static ProbTransition t1(&initial_state, &initial_state, 1.00, 'P'); //0.01 chance that X is actually Q
      static ProbTransition t1(&initial_state, &q_happened, 1.00, 'Q'); //0.01 chance that X is actually Q
      static ProbTransition t1(&q_happened, &p_happened_after_q, 1.00, 'P'); //0.01 chance that X is actually Q
      static ProbTransition t1(&p_happened_after_q, &r_happened_after_q_and_p, 1.00, 'R'); //0.01 chance that X is actually Q
      //todo: finish transitions
      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&b);
    }
};