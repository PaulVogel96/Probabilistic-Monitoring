#ifndef UniversalityAfterQProperty_hpp
#define UniversalityAfterQProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"After Q, it is always the case that P holds 
class UniversalityAfterQProperty : public ProbStatemachine {
  public:
    UniversalityAfterQProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* q_happened = new State("Q happened", Verdict::SATISFIED);
      auto* not_p_happened_after_q = new State("not P happened after Q", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_happened, 1.00, EVENT_Q);
      auto* t2 = new AllRequiredEventsInactiveTransition(q_happened, not_p_happened_after_q, 1.00, EVENT_P);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(q_happened);
      this->addState(not_p_happened_after_q);
    }
};
#endif