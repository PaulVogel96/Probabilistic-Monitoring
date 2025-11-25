#ifndef ResponseAfterQProperty_hpp
#define ResponseAfterQProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//After Q, if P happens, then in response S eventually holds
class ResponseAfterQProperty : public ProbStatemachine {
  public:
    ResponseAfterQProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* q_happened = new State("Q happened", Verdict::SATISFIED);
      auto* p_happened = new State("P happened", Verdict::INCONCLUSIVE);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_happened, 1.0, EVENT_Q);
      auto* t2 = new AllRequiredEventsActiveTransition(q_happened, p_happened, 1.0, EVENT_P);
      auto* t3 = new AllRequiredEventsActiveTransition(p_happened, q_happened, 1.0, EVENT_S);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(q_happened);
      this->addState(p_happened);
    }
};
#endif