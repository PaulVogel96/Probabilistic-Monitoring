#ifndef PrecedenceProperty_hpp
#define PrecedenceProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"After Q holds, if P holds then it must be that case that S holds before P"
class PrecedenceAfterQProperty : public ProbStatemachine {
  public:
    PrecedenceAfterQProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> q_happened("Q happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> s_happened("S happened", Verdict::SATISFIED);
      static State<ProbTransition> p_happened("P happened", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_happened, 1.0, EVENT_Q);
      static AllRequiredEventsActiveTransition t2(&q_happened, &p_happened, 1.0, EVENT_P);
      static AllRequiredEventsActiveTransition t3(&q_happened, &s_happened, 1.0, EVENT_S);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&p_happened);
      this->addState(&s_happened);
      this->addState(&q_happened);
    }
};
#endif