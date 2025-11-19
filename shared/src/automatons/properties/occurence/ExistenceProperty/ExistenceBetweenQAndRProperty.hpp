#ifndef ExistenceBetweenQAndRProperty_hpp
#define ExistenceBetweenQAndRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"Between Q and R, it is eventually the case that P holds"
class ExistenceBetweenQAndRProperty : public ProbStatemachine {
  public:
    ExistenceBetweenQAndRProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* q_happened = new State("Q happened", Verdict::INCONCLUSIVE);
      auto* p_after_q = new State("P happened after Q", Verdict::INCONCLUSIVE);
      auto* not_p_or_r = new State("Not P or R happened after Q", Verdict::INCONCLUSIVE);
      auto* error = new State("Error", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_happened, 1.0, EVENT_Q);
      auto* t2 = new AllRequiredEventsActiveTransition(q_happened, initial_state, 1.00, EVENT_R);
      auto* t3 = new AllRequiredEventsActiveTransition(q_happened, p_after_q, 1.0, EVENT_P);
      auto* t4 = new AllRequiredEventsActiveTransition(p_after_q, initial_state, 1.0, EVENT_R);
      auto* t5 = new AllRequiredEventsInactiveTransition(q_happened, not_p_or_r, 1.00, EVENT_P | EVENT_R);
      auto* t6 = new AllRequiredEventsActiveTransition(not_p_or_r, p_after_q, 1.0, EVENT_P);
      auto* t7 = new AllRequiredEventsActiveTransition(not_p_or_r, error, 1.0, EVENT_R);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(q_happened);
      this->addState(p_after_q);
      this->addState(not_p_or_r);
      this->addState(error);
    }
};
#endif