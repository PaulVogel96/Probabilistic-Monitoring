#include "../../../State.hpp"
#include "../../../ProbTransition.hpp"
#include "../../../ProbStatemachine.hpp"

/*
This property describe the universal existance of an event 
In structure english we can formulate it as:
"It is always the case that P holds after Q holds"
The property is violated when:
1. Q happens and P does not happens afterwards
In this implementation: 
- the char "P" indicates that P has happened
- the char "Q" indicates that Q has happened
- the char "X" indicates that neither Q nor P has happened
Here, we model the uncertainty in the value of the event P
There is a 0.01 chance for any P event to actually be X (not P)

Transitions where P behaves as X (not P) are only modeled when this behaviour differs from "normal" P behavior
*/
class UniversalityAfterQProperty : public ProbStatemachine {
  public:
    UniversalityAfterQProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::SATISFIED);
      static State<ProbTransition> p_happened_after_q("P happened after Q", Verdict::SATISFIED);
      static State<ProbTransition> not_p_happened_after_q("not P happened after Q", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &q_happened, 1.00, 'Q');
      static ProbTransition t2(&q_happened, &p_happened_after_q, 0.99, 'P');
      static ProbTransition t3(&q_happened, &not_p_happened_after_q, 0.01, 'P');
      static ProbTransition t4(&q_happened, &not_p_happened_after_q, 1.00, 'Q');
      static ProbTransition t5(&q_happened, &not_p_happened_after_q, 1.00, 'X');
      static ProbTransition t6(&p_happened_after_q, &not_p_happened_after_q, 1.00, 'X');

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&q_happened);
      this->addState(&p_happened_after_q);
      this->addState(&not_p_happened_after_q);
    }
};