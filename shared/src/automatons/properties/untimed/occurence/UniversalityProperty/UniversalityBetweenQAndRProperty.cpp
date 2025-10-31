#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
This property describe the universality of an event 
In structure english we can formulate it as:
"It is always the case that P holds between Q and R"
The property is violated when:
1. Q happens and not P happens and then R happens
In this implementation: 
- the char "P" indicates that P has happened
- the char "Q" indicates that Q has happened
- the char "R" indicates that R has happened 
- the char "X" indicates that neither P nor Q nor R has happened
Here, we model the uncertainty in the value of the event P
there is a 0.01 chance that P behaves as not P

Transitions where X behaves as another event are all modeled when this behaviour differs from "normal" X behavior
*/
class UniversalityBetweenQAndRProperty : public ProbStatemachine {
  public:
    UniversalityBetweenQAndRProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::SATISFIED);
      static State<ProbTransition> p_happened_after_q("P happened after Q", Verdict::SATISFIED);
      static State<ProbTransition> not_p_happened_after_q("Not P happened after Q", Verdict::SATISFIED);
      static State<ProbTransition> r_happened_after_q_and_not_p("R happened after Q and P", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &q_happened, 1.00, 'Q');
      static ProbTransition t2(&q_happened, &p_happened_after_q, 0.99, 'P');
      static ProbTransition t3(&q_happened, &not_p_happened_after_q, 0.01, 'P');
      static ProbTransition t4(&q_happened, &not_p_happened_after_q, 1.0, 'X');
      static ProbTransition t5(&q_happened, &initial_state, 1.0, 'R');
      static ProbTransition t6(&p_happened_after_q, &initial_state, 1.00, 'R');
      static ProbTransition t7(&not_p_happened_after_q, &r_happened_after_q_and_not_p, 1.00, 'R');
      
      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&q_happened);
      this->addState(&p_happened_after_q);
      this->addState(&not_p_happened_after_q);
      this->addState(&r_happened_after_q_and_not_p);
    }
};