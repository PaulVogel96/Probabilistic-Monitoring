#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
This property describe the existence of an event.
In structure english we can formulate it as:
"After Q, if P then it must be that case that S before P"

X indicates not P

Here, we model the uncertainty in the value of the event P
There is a 0.01 chance for any P event to actually be not P 
*/
class PrecedenceAfterQProperty : public ProbStatemachine {
  public:
    PrecedenceAfterQProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> q_happened("Q happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> s_happened("S happened", Verdict::SATISFIED);
      static State<ProbTransition> p_happened("P happened", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &q_happened, 1.0, 'Q');
      static ProbTransition t2(&q_happened, &p_happened, 0.99, 'P');
      static ProbTransition t3(&q_happened, &q_happened, 0.01, 'P');
      static ProbTransition t4(&q_happened, &s_happened, 1.0, 'S');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&p_happened);
      this->addState(&s_happened);
      this->addState(&q_happened);
    }
};