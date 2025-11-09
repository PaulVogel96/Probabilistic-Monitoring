#ifndef UntilBeforeRProperty_hpp
#define UntilBeforeRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AnyRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"P holds until S holds until R holds"
class UntilBeforeRProperty : public ProbStatemachine {
  public:
    UntilBeforeRProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::VIOLATED);
      static State<ProbTransition> s_or_r_holds("S or R after P", Verdict::SATISFIED);
      static State<ProbTransition> not_p_holds("Not P", Verdict::VIOLATED);

      static AnyRequiredEventsActiveTransition t1(&initial_state, &s_or_r_holds, 1.0, EVENT_S | EVENT_R);
      static AllRequiredEventsInactiveTransition t2(&initial_state, &not_p_holds, 1.0, EVENT_P | EVENT_S | EVENT_R);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&s_or_r_holds);
      this->addState(&not_p_holds);
    }
};
#endif