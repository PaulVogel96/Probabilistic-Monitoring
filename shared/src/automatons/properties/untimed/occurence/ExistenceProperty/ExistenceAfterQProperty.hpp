#ifndef ExistenceAfterQProperty_hpp
#define ExistenceAfterQProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"After Q holds, it is eventually the case that P holds"
class ExistenceAfterQProperty : public ProbStatemachine {
  public:
    ExistenceAfterQProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* q_has_happened = new State("Q happened", Verdict::VIOLATED);
      auto* p_after_q = new State("P happened after Q", Verdict::SATISFIED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_has_happened, 1.0, EVENT_Q);
      auto* t2 = new AllRequiredEventsActiveTransition(q_has_happened, p_after_q, 1.0, EVENT_P);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(q_has_happened);
      this->addState(p_after_q);
    }
};
#endif