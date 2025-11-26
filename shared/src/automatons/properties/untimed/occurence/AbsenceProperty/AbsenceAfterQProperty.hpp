#ifndef AbsenceAfterQProperty_hpp
#define AbsenceAfterQProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"It is never the case that P holds after Q holds"
class AbsenceAfterQProperty : public ProbStatemachine {
  public:
    AbsenceAfterQProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::INCONCLUSIVE);
      auto* q_happened = new State("Q happened", Verdict::INCONCLUSIVE);
      auto* p_after_q = new State("P happened after Q", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_happened, 1.00, EVENT_Q);
      auto* t2 = new AllRequiredEventsActiveTransition(q_happened, p_after_q, 1.00, EVENT_P);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(q_happened);
      this->addState(p_after_q);
    }
};
#endif