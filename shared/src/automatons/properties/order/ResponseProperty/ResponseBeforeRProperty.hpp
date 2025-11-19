#ifndef ResponseBeforeRProperty_hpp
#define ResponseBeforeRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"Before R holds, If P holds, then in response S eventually holds"
class ResponseBeforeRProperty : public ProbStatemachine {
  public:
    ResponseBeforeRProperty() : ProbStatemachine() {
      auto* initial_state = new State<ProbTransition>("Initial State", Verdict::SATISFIED);
      auto* p_happened = new State<ProbTransition>("P happened before S", Verdict::INCONCLUSIVE);
      auto* r_after_p = new State<ProbTransition>("R happened after P", Verdict::VIOLATED);
      auto* r_without_p = new State<ProbTransition>("R happened", Verdict::SATISFIED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, p_happened, 1.0, EVENT_P);
      auto* t2 = new AllRequiredEventsActiveTransition(p_happened, initial_state, 1.0, EVENT_S);
      auto* t3 = new AllRequiredEventsActiveTransition(p_happened, r_after_p, 1.0, EVENT_R);
      auto* t4 = new AllRequiredEventsActiveTransition(initial_state, r_without_p, 1.0, EVENT_R);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_happened);
      this->addState(r_after_p);
      this->addState(r_without_p);
    }
};
#endif