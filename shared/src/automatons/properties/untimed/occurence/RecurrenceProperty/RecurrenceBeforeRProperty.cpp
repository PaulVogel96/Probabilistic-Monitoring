#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
This property describe the repeated holding of property.
In structure english we can formulate it as:
"Before R, P holds repeatedly"
In this implementation, the char "P" indicates that P holds
X indicates that P does not hold
R indicates that R holds

Here, we model the uncertainty in the value of the event P
There is a 0.01 chance for any P event to actually be not P
*/
class RecurrenceBeforeRProperty : public ProbStatemachine {
  public:
    RecurrenceBeforeRProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_holds("P happened", Verdict::SATISFIED);
      static State<ProbTransition> r_reached1("R reached", Verdict::INCONCLUSIVE);
      static State<ProbTransition> r_reached2("R reached", Verdict::SATISFIED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &initial_state, 0.01, 'P');
      static ProbTransition t2(&initial_state, &p_holds, 0.99, 'P');
      static ProbTransition t3(&p_holds, &initial_state, 1.0, 'X');
      static ProbTransition t4(&initial_state, &r_reached1, 1.0, 'R');
      static ProbTransition t5(&p_holds, &r_reached2, 1.0, 'R');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&p_holds);
      this->addState(&r_reached1);
      this->addState(&r_reached2);
    }
};