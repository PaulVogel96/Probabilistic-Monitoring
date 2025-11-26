#ifndef AbsenceBetweenQAndRProperty_hpp
#define AbsenceBetweenQAndRProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"It is never the case that P holds between Q and R"
class AbsenceBetweenQAndRProperty : public ProbStatemachine {
  public:
    AbsenceBetweenQAndRProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* q_happened = new State("Q happened", Verdict::SATISFIED);
      auto* p_after_q = new State("P happened after Q", Verdict::SATISFIED);
      auto* r_after_q_and_p = new State("R happened after Q and P", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_happened, 1.00, EVENT_Q);
      auto* t2 = new AllRequiredEventsActiveTransition(q_happened, p_after_q, 1.00, EVENT_P);
      auto* t3 = new AllRequiredEventsActiveTransition(q_happened, initial_state, 1.00, EVENT_R);
      auto* t4 = new AllRequiredEventsActiveTransition(p_after_q, r_after_q_and_p, 1.00, EVENT_R);
      
      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(q_happened);
      this->addState(p_after_q);
      this->addState(r_after_q_and_p);
    }
};
#endif