#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
In structure english we can formulate it as:
"After Q holds, P holds without interruption until S holds before R holds
"
In this implementation, the char "P" indicates that P has happened
X indicates not P

Here, we model the uncertainty in the value of the event "P"
There is a 0.01 chance for any P event to actually be not P 
*/
class UntilBetweenQAndRProperty : public ProbStatemachine {
  public:
    UntilBetweenQAndRProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_holds("Q holds", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_holds("P holds", Verdict::INCONCLUSIVE);
      static State<ProbTransition> not_p_holds_before_p("P holds", Verdict::INCONCLUSIVE);
      static State<ProbTransition> not_p_holds_after_p("P holds", Verdict::VIOLATED);
      static State<ProbTransition> s_holds("S holds", Verdict::INCONCLUSIVE);
      static State<ProbTransition> r_holds("R holds (but PS did not)", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &q_holds, 1.00, 'Q');

      static ProbTransition t2(&q_holds, &initial_state, 1.00, 'R');
      static ProbTransition t3(&q_holds, &p_holds, 0.99, 'P');
      static ProbTransition t4(&q_holds, &not_p_holds_before_p, 0.01, 'P');
      static ProbTransition t5(&q_holds, &not_p_holds_before_p, 1.0, 'X');
    
      static ProbTransition t6(&not_p_holds_before_p, &p_holds, 0.99, 'P');
      static ProbTransition t7(&not_p_holds_before_p, &not_p_holds_before_p, 0.01, 'P');

      static ProbTransition t8(&p_holds, &not_p_holds_after_p, 1.0, 'X');
      static ProbTransition t9(&p_holds, &s_holds, 1.0, 'S');
      static ProbTransition t10(&p_holds, &r_holds, 1.0, 'R');

      static ProbTransition t11(&s_holds, &initial_state, 1.0, 'R');
      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&q_holds);
      this->addState(&p_holds);
      this->addState(&not_p_holds_after_p);
      this->addState(&not_p_holds_before_p);
      this->addState(&s_holds);
      this->addState(&r_holds);
    }
};