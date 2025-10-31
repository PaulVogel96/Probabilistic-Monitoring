#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
This property describe the existence of an event.
In structure english we can formulate it as:
"It is eventually the case that P holds after Q holds and before R holds"
In this implementation, the char "P" indicates that P has happened
R indicates that R has happened
Q indicates that Q has happened
X indicates that P has not happened

Here, we model the uncertainty in the value of the event P
There is a 0.01 chance for any P event to actually be not P 
*/
class ExistenceBetweenQAndRProperty : public ProbStatemachine {
  public:
    ExistenceBetweenQAndRProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_after_q("P happened after Q", Verdict::INCONCLUSIVE);
      static State<ProbTransition> x_after_q("Not P or R happened after Q", Verdict::INCONCLUSIVE);
      static State<ProbTransition> error("Error", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &q_happened, 1.0, 'Q');
      static ProbTransition t2(&q_happened, &p_after_q, 0.99, 'P');
      static ProbTransition t3(&q_happened, &q_happened, 0.01, 'P');
      static ProbTransition t4(&p_after_q, &initial_state, 1.0, 'R');

      static ProbTransition t5(&q_happened, &initial_state, 1.00, 'R');
      static ProbTransition t6(&q_happened, &x_after_q, 1.00, 'X');

      static ProbTransition t7(&x_after_q, &p_after_q, 0.99, 'P');
      static ProbTransition t8(&x_after_q, &x_after_q, 0.01, 'P');
      static ProbTransition t9(&x_after_q, &error, 1.0, 'R');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&q_happened);
      this->addState(&p_after_q);
      this->addState(&x_after_q);
      this->addState(&error);
    }
};