#ifndef ResponseBetweenQAndRProperty_hpp
#define ResponseBetweenQAndRProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//Between Q and R, if P holds, in response S eventually holds
class ResponseBetweenQAndRProperty : public ProbStatemachine {
  public:
    ResponseBetweenQAndRProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* q_happened = new State("Q happened", Verdict::SATISFIED);
      auto* p_happened = new State("P happened", Verdict::INCONCLUSIVE);
      auto* r_without_s = new State("R happened before S did", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_happened, 1.0, EVENT_Q);
      auto* t2 = new AllRequiredEventsActiveTransition(q_happened, initial_state, 1.0, EVENT_R);
      auto* t3 = new AllRequiredEventsActiveTransition(q_happened, p_happened, 1.0, EVENT_P);
      auto* t4 = new AllRequiredEventsActiveTransition(p_happened, initial_state, 1.0, EVENT_S);
      auto* t5 = new AllRequiredEventsActiveTransition(p_happened, r_without_s, 1.0, EVENT_R);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(q_happened);
      this->addState(p_happened);
      this->addState(r_without_s);
    }
};
#endif