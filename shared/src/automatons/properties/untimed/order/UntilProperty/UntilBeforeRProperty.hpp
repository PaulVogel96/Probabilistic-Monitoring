#ifndef UntilBeforeRProperty_hpp
#define UntilBeforeRProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/AnyRequiredEventsActiveTransition.hpp"
#include "../../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"P holds until S holds until R holds"
class UntilBeforeRProperty : public ProbStatemachine {
  public:
    UntilBeforeRProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::VIOLATED);
      auto* s_or_r_holds = new State("S or R after P", Verdict::SATISFIED);
      auto* not_p_holds = new State("Not P", Verdict::VIOLATED);

      auto* t1 = new AnyRequiredEventsActiveTransition(initial_state, s_or_r_holds, 1.0, EVENT_S | EVENT_R);
      auto* t2 = new AllRequiredEventsInactiveTransition(initial_state, not_p_holds, 1.0, EVENT_P | EVENT_S | EVENT_R);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(s_or_r_holds);
      this->addState(not_p_holds);
    }
};
#endif