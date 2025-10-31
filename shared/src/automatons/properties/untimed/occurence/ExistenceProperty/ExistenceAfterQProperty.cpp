#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
This property describe the existence of an event.
In structure english we can formulate it as:
"It is eventually the case that P holds after Q holds"
In this implementation, the char "P" indicates that P has happened
X indicates that P has not happened
Q indicates that Q has happened

Here, we model the uncertainty in the value of the event P
There is a 0.01 chance for any P event to actually be not P 
*/
class ExistenceAfterQProperty : public ProbStatemachine {
  public:
    ExistenceAfterQProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_has_happened("Q happened", Verdict::VIOLATED);
      static State<ProbTransition> p_after_q("P happened after Q", Verdict::SATISFIED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &q_has_happened, 1.0, 'Q');
      static ProbTransition t2(&q_has_happened, &p_after_q, 0.99, 'P');
      static ProbTransition t3(&q_has_happened, &q_has_happened, 0.01, 'P');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&q_has_happened);
      this->addState(&p_after_q);
    }
};