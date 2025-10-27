#include "../../../../State.hpp"
#include "../../../../ProbTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

/*
This property describe the existence of an event.
In structure english we can formulate it as:
"It is eventually the case that P happens before R happens"
In this implementation, the char "P" indicates that P has happened
X indicates that P has not happened
R indicates that R holds

Here, we model the uncertainty in the value of the event P
There is a 0.01 chance for any P event to actually be not P 
*/
class ExistenceBeforeRProperty : public ProbStatemachine {
  public:
    ExistenceBeforeRProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> p_has_happened("P happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> r_has_happened_after_p("R happened after P", Verdict::SATISFIED);
      static State<ProbTransition> r_has_happened_without_p("P did not happen, but R did", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &p_has_happened, 0.99, 'P');
      static ProbTransition t2(&initial_state, &initial_state, 0.01, 'P');
      static ProbTransition t3(&initial_state, &r_has_happened_without_p, 1.0, 'R');
      static ProbTransition t4(&p_has_happened, &r_has_happened_after_p, 1.0, 'R');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&p_has_happened);
      this->addState(&r_has_happened_after_p);
      this->addState(&r_has_happened_without_p);
    }
};