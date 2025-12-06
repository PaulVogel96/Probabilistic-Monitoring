#ifndef PrecedenceBeforeRProperty_hpp
#define PrecedenceBeforeRProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"Before R holds, if P holds then it must be that case that S holds before P"
class PrecedenceBeforeRProperty : public ProbStatemachine {
  public:
    PrecedenceBeforeRProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::INCONCLUSIVE);
      auto* before_p = new State("S or R happened before P", Verdict::SATISFIED);
      auto* p_happened = new State("S happened", Verdict::INCONCLUSIVE);
      auto* after_p = new State("S or R happened after P", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, before_p, 1.0, EVENT_S);
      auto* t2 = new AllRequiredEventsActiveTransition(initial_state, before_p, 1.0, EVENT_R);
      auto* t3 = new AllRequiredEventsActiveTransition(initial_state, p_happened, 1.0, EVENT_P);
      auto* t4 = new AllRequiredEventsActiveTransition(p_happened, after_p, 1.0, EVENT_R);
      auto* t5 = new AllRequiredEventsActiveTransition(p_happened, after_p, 1.0, EVENT_S);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(before_p);
      this->addState(p_happened);
      this->addState(after_p);
    }
};
#endif