#ifndef ResponseProperty_hpp
#define ResponseProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"If P holds, then in response S eventually holds"
class ResponseProperty : public ProbStatemachine {
  public:
    ResponseProperty() : ProbStatemachine() {
      auto* initial_state = new State<ProbTransition>("Initial State", Verdict::SATISFIED);
      auto* p_happened = new State<ProbTransition>("P happened", Verdict::INCONCLUSIVE);
      auto* s_happened = new State<ProbTransition>("S happened", Verdict::SATISFIED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, p_happened, 1.0, EVENT_P);
      auto* t2 = new AllRequiredEventsActiveTransition(p_happened, s_happened, 1.0, EVENT_S);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_happened);
      this->addState(s_happened);
    }
};
#endif