#ifndef UntilProperty_hpp
#define UntilProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"P holds until S holds"
class UntilProperty : public ProbStatemachine {
  public:
    UntilProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::INCONCLUSIVE);
      auto* s_holds = new State("S", Verdict::SATISFIED);
      auto* not_p_or_s_holds = new State("NOT_P", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsInactiveTransition(initial_state, not_p_or_s_holds, 1.0, EVENT_P | EVENT_S);
      auto* t2 = new AllRequiredEventsActiveTransition(initial_state, s_holds, 1.0, EVENT_S);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(s_holds);
      this->addState(not_p_or_s_holds);
    }
};
#endif