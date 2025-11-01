#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

/*
This property describe the existence of an event.
In structure english we can formulate it as:
"between Q and R, if P then it must be that case that S before P"

X indicates not P

Here, we model the uncertainty in the value of the event P
There is a 0.01 chance for any P event to actually be not P 
*/

//TODO: why is there a second "not P nor S nor R" state in PAP?
class PrecedenceBetweenQAndRProperty : public ProbStatemachine {
  public:
    PrecedenceBetweenQAndRProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::VIOLATED);
      static State<ProbTransition> not_p_nor_s("Neither P nor S happened", Verdict::VIOLATED);
      static State<ProbTransition> s_happened("S happened", Verdict::SATISFIED);
      static State<ProbTransition> p_before_s("P happened before S", Verdict::INCONCLUSIVE);
      static State<ProbTransition> error("R happened after P", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &q_happened, 1.0, 'Q');
      static ProbTransition t2(&q_happened, &initial_state, 1.0, 'R');
      static ProbTransition t3(&q_happened, &s_happened, 1.0, 'S');
      static ProbTransition t4(&q_happened, &not_p_nor_s, 1.0, 'X');
      static ProbTransition t5(&not_p_nor_s, &p_before_s, 0.99, 'P');
      static ProbTransition t6(&not_p_nor_s, &not_p_nor_s, 0.01, 'P');
      static ProbTransition t7(&p_before_s, &error, 1.0, 'R');
      static ProbTransition t8(&p_before_s, &error, 1.0, 'S');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&q_happened);
      this->addState(&not_p_nor_s);
      this->addState(&s_happened);
      this->addState(&p_before_s);
      this->addState(&error);
    }
};