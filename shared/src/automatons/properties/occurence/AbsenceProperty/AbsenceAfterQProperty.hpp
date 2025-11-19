#ifndef AbsenceAfterQProperty_hpp
#define AbsenceAfterQProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"It is never the case that P holds after Q holds"
class AbsenceAfterQProperty : public ProbStatemachine {
  public:
    AbsenceAfterQProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> q_happened("Q happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_after_q("P happened after Q", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_happened, 1.00, EVENT_Q);
      static AllRequiredEventsActiveTransition t2(&q_happened, &p_after_q, 1.00, EVENT_P);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&q_happened);
      this->addState(&p_after_q);
    }
};
#endif