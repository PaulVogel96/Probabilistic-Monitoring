#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
This property describes the Universality of an event before the  
In structure english we can formulate it as:
"It is always the case that P holds before R holds"
The property is violated in two cases:
1. P happens, but R never happens
1. R happens and P happens afterwards
In this implementation: 
- the char "P" indicates that P
- the char "R" indicates that R
- the char "X" indicates that neither R nor P
Here, we model the uncertainty in the value of the event P

Loop- / Selftransitions are only declared when they don't happen with 1.00 probability
*/
class UniversalityBeforeRProperty : public ProbStatemachine {
  public:
    UniversalityBeforeRProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> r_has_happened("R happened", Verdict::SATISFIED);
      static State<ProbTransition> p_has_happened("P happened", Verdict::SATISFIED);
      static State<ProbTransition> x_has_happened("X happened", Verdict::SATISFIED);
      static State<ProbTransition> r_has_happened_after_p("R happened after P", Verdict::SATISFIED);
      static State<ProbTransition> x_has_happened_after_p("X happened after P", Verdict::VIOLATED);
      static State<ProbTransition> r_has_happened_after_x("R happened after X", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &initial_state, 0.01, 'P');
      static ProbTransition t2(&initial_state, &p_has_happened, 0.99, 'P');
      static ProbTransition t3(&p_has_happened, &x_has_happened_after_p, 0.01, 'P');
      static ProbTransition t4(&p_has_happened, &p_has_happened, 0.99, 'P');
      static ProbTransition t5(&p_has_happened, &x_has_happened_after_p, 1.0, 'X');
      static ProbTransition t6(&p_has_happened, &r_has_happened_after_p, 1.0, 'R');
      static ProbTransition t7(&initial_state, &r_has_happened, 1.00, 'R');
      static ProbTransition t8(&initial_state, &x_has_happened, 1.00, 'X');
      static ProbTransition t9(&x_has_happened, &r_has_happened_after_x, 1.00, 'R');

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&r_has_happened);
      this->addState(&p_has_happened);
      this->addState(&x_has_happened);
      this->addState(&r_has_happened_after_p);
      this->addState(&x_has_happened_after_p);
      this->addState(&r_has_happened_after_x);
    }
};