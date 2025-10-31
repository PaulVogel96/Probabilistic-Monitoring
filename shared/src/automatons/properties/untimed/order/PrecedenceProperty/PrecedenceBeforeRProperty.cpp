#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
This property describe the existence of an event.
In structure english we can formulate it as:
"Before R if P then it must be that case that S before P"

X indicates not P

Here, we model the uncertainty in the value of the event P
There is a 0.01 chance for any P event to actually be not P 
*/
class PrecedenceBeforeRProperty : public ProbStatemachine {
  public:
    PrecedenceBeforeRProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> before_p("S or R happened before P", Verdict::SATISFIED);
      static State<ProbTransition> p_happened("S happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> after_p("S or R happened after P", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &before_p, 1.0, 'S');
      static ProbTransition t2(&initial_state, &before_p, 1.0, 'R');
      static ProbTransition t3(&initial_state, &p_happened, 0.99, 'P');
      static ProbTransition t4(&initial_state, &initial_state, 0.01, 'P');
      static ProbTransition t5(&p_happened, &after_p, 1.0, 'R');
      static ProbTransition t6(&p_happened, &after_p, 1.0, 'S');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&before_p);
      this->addState(&p_happened);
      this->addState(&after_p);
    }
};