#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
In structure english we can formulate it as:
"P holds without interruption until S holds after Q holds
"
In this implementation, the char "P" indicates that P has happened
X indicates not P

Here, we model the uncertainty in the value of the event "P"
There is a 0.01 chance for any P event to actually be not P 
*/
class UntilAfterQProperty : public ProbStatemachine {
  public:
    UntilAfterQProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_holds("Q", Verdict::INCONCLUSIVE);
      static State<ProbTransition> s_holds("S", Verdict::SATISFIED);
      static State<ProbTransition> error("Error State", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &q_holds, 1.00, 'Q');
      static ProbTransition t2(&q_holds, &s_holds, 1.00, 'S');
      static ProbTransition t3(&q_holds, &q_holds, 0.99, 'P');
      static ProbTransition t4(&q_holds, &error, 0.01, 'P');
      static ProbTransition t5(&q_holds, &error, 1.0, 'X');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&q_holds);
      this->addState(&s_holds);
      this->addState(&error);
    }
};