#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
In structure english we can formulate it as:
"P holds until S holds
"
In this implementation, the char "P" indicates that P has happened
X indicates not P

Here, we model the uncertainty in the value of the event "P"
There is a 0.01 chance for any P event to actually be not P 
*/
class UntilProperty : public ProbStatemachine {
  public:
    UntilProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State (P)", Verdict::SATISFIED);
      static State<ProbTransition> s_holds("S", Verdict::SATISFIED);
      static State<ProbTransition> not_p_holds("NOT_P", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &initial_state, 0.99, 'P');
      static ProbTransition t2(&initial_state, &not_p_holds, 0.01, 'P');
      static ProbTransition t3(&initial_state, &not_p_holds, 1.00, 'X');
      static ProbTransition t3(&initial_state, &s_holds, 1.00, 'S');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&s_holds);
      this->addState(&not_p_holds);
    }
};