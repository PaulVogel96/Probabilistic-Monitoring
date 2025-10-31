#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
This property describe the repeated holding of property.
In structure english we can formulate it as:
"Between Q and R, P holds repeatedly"
In this implementation, the char "P" indicates that P holds
X indicates that P does not hold
Q indicates that Q holds
R indicates that R holds

Here, we model the uncertainty in the value of the event P
There is a 0.01 chance for any P event to actually be not P
*/
class RecurrenceProperty : public ProbStatemachine {
  public:
    RecurrenceProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> q_happened("Q happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_happened("Q happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> not_p_happened("P did not happen", Verdict::INCONCLUSIVE);
      static State<ProbTransition> r_happened("P did not happen", Verdict::SATISFIED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &q_happened, 1.0, 'Q');
      static ProbTransition t1(&q_happened, &q_happened, 0.01, 'P');
      static ProbTransition t1(&q_happened, &p_happened, 0.99, 'P');
      static ProbTransition t1(&p_happened, &not_p_happened, 1.0, 'X');
      static ProbTransition t1(&not_p_happened, &r_happened, 1.0, 'R');
      static ProbTransition t1(&q_happened, &r_happened, 1.0, 'R');
      static ProbTransition t1(&p_happened, &r_happened, 1.0, 'R');
      static ProbTransition t1(&r_happened, &q_happened, 1.0, 'R');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&q_happened);
      this->addState(&p_happened);
      this->addState(&not_p_happened);
      this->addState(&r_happened);
    }
};