#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
This property describe the existence of an event.
In structure english we can formulate it as:
"It is eventually the case that P holds"
In this implementation, the char "P" indicates that P has happened
X indicates that P has not happened
Here, we model the uncertainty in the value of the event P
There is a 0.01 chance for any P event to actually be not P 
*/
class ExistenceProperty : public ProbStatemachine {
  public:
    ExistenceProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_has_happened("P happened", Verdict::SATISFIED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &initial_state, 0.01, 'P');
      static ProbTransition t2(&initial_state, &p_has_happened, 0.99, 'P');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&p_has_happened);
    }
};