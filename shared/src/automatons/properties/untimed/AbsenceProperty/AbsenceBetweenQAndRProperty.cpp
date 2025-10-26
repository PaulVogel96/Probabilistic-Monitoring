#include "../../../../State.hpp"
#include "../../../../ProbTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

/*
This property describe the absence of an event 
In structured english we can formulate it as:
"It is never the case that P holds between Q and R"
The property is violated when:
1. Q happens and P happens afterwards and then R happens
In this implementation: 
- the char "P" indicates that P has happened
- the char "Q" indicates that Q has happened
- the char "R" indicates that R has happened 
- the char "X" indicates that neither R nor P has happened
Here, we model the uncertainty in the value of the event X
There is a 0.01 chance for any X event to actually be a P and
there is a 0.01 chance for any X event to actually be a Q and
there is a 0.01 chance for any X event to actually be a R

Transitions where X behaves as another event are all modeled when this behaviour differs from "normal" X behavior
*/
class AbsenceBetweenQAndRProperty : public ProbStatemachine {
  public:
    AbsenceBetweenQAndRProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::SATISFIED);
      static State<ProbTransition> p_happened_after_q("P happened after Q", Verdict::SATISFIED);
      static State<ProbTransition> r_happened_after_q_and_p("R happened after Q and P", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &initial_state, 0.99, 'X');
      static ProbTransition t2(&initial_state, &q_happened, 0.01, 'X'); //0.01 chance that X is actually Q
      static ProbTransition t3(&initial_state, &q_happened, 1.00, 'Q');

      static ProbTransition t4(&q_happened, &q_happened, 0.99, 'X');
      static ProbTransition t5(&q_happened, &p_happened_after_q, 0.01, 'X'); //0.01 chance that X is actually P
      static ProbTransition t6(&q_happened, &p_happened_after_q, 1.00, 'P'); //0.01 chance that X is actually Q

      static ProbTransition t7(&p_happened_after_q, &p_happened_after_q, 0.99, 'X');
      static ProbTransition t8(&p_happened_after_q, &r_happened_after_q_and_p, 0.01, 'X'); //0.01 chance that X is actually R
      static ProbTransition t9(&p_happened_after_q, &r_happened_after_q_and_p, 1.00, 'R'); //0.01 chance that X is actually Q
      
      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&q_happened);
      this->addState(&p_happened_after_q);
      this->addState(&r_happened_after_q_and_p);
    }
};