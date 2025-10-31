#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
In structure english we can formulate it as:
"If, then in response S eventually holds before R holds"

X indicates not P

Here, we model the uncertainty in the value of the event P
There is a 0.01 chance for any P event to actually be not P 
*/
class ResponseProperty : public ProbStatemachine {
  public:
    ResponseProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> p_happened("P happened before S", Verdict::INCONCLUSIVE);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &initial_state, 0.01, 'P');
      static ProbTransition t2(&initial_state, &p_happened, 0.99, 'P');
      static ProbTransition t3(&p_happened, &initial_state, 1.0, 'S');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&p_happened);
    }
};