#ifndef PrecedenceAfterQProperty_hpp
#define PrecedenceAfterQProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"After Q holds, if P holds then it must be that case that S holds before P"
class PrecedenceAfterQProperty : public ProbStatemachine {
  public:
    PrecedenceAfterQProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::INCONCLUSIVE);
      auto* q_happened = new State("Q happened", Verdict::INCONCLUSIVE);
      auto* s_happened = new State("S happened", Verdict::SATISFIED);
      auto* p_happened = new State("P happened", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_happened, 1.0, EVENT_Q);
      auto* t2 = new AllRequiredEventsActiveTransition(q_happened, p_happened, 1.0, EVENT_P);
      auto* t3 = new AllRequiredEventsActiveTransition(q_happened, s_happened, 1.0, EVENT_S);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_happened);
      this->addState(s_happened);
      this->addState(q_happened);
    }
};
#endif