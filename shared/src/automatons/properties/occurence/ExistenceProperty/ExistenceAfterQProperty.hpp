#ifndef ExistenceAfterQProperty_hpp
#define ExistenceAfterQProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"After Q holds, it is eventually the case that P holds"
class ExistenceAfterQProperty : public ProbStatemachine {
  public:
    ExistenceAfterQProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_has_happened("Q happened", Verdict::VIOLATED);
      static State<ProbTransition> p_after_q("P happened after Q", Verdict::SATISFIED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_has_happened, 1.0, EVENT_Q);
      static AllRequiredEventsActiveTransition t2(&q_has_happened, &p_after_q, 1.0, EVENT_P);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&q_has_happened);
      this->addState(&p_after_q);
    }
};
#endif