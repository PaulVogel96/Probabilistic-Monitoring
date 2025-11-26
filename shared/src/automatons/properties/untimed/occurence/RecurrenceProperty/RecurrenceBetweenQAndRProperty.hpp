#ifndef RecurrenceBetweenQAndRProperty_hpp
#define RecurrenceBetweenQAndRProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../transitions/untimed/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"Between Q and R, P holds repeatedly"
class RecurrenceBetweenQAndRProperty : public ProbStatemachine {
  public:
    RecurrenceBetweenQAndRProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::INCONCLUSIVE);
      auto* q_happened = new State("Q happened", Verdict::INCONCLUSIVE);
      auto* p_happened = new State("Q happened", Verdict::INCONCLUSIVE);
      auto* not_p_happened = new State("P did not happen", Verdict::INCONCLUSIVE);
      auto* r_happened = new State("P did not happen", Verdict::SATISFIED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_happened, 1.0, EVENT_Q);
      auto* t2 = new AllRequiredEventsActiveTransition(q_happened, r_happened, 1.0, EVENT_R);
      auto* t3 = new AllRequiredEventsActiveTransition(q_happened, p_happened, 1.0, EVENT_P);
      auto* t4 = new AllRequiredEventsInactiveTransition(p_happened, not_p_happened, 1.0, EVENT_P | EVENT_R);
      auto* t5 = new AllRequiredEventsActiveTransition(not_p_happened, r_happened, 1.0, EVENT_R);
      auto* t6 = new AllRequiredEventsActiveTransition(p_happened, r_happened, 1.0, EVENT_R);
      auto* t7 = new AllRequiredEventsActiveTransition(r_happened, q_happened, 1.0, EVENT_R);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(q_happened);
      this->addState(p_happened);
      this->addState(not_p_happened);
      this->addState(r_happened);
    }
};
#endif