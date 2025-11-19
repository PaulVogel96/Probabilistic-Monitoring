#ifndef RecurrenceBeforeRProperty_hpp
#define RecurrenceBeforeRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"Before R holds, P holds repeatedly"
class RecurrenceBeforeRProperty : public ProbStatemachine {
  public:
    RecurrenceBeforeRProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::INCONCLUSIVE);
      auto* p_holds = new State("P happened", Verdict::SATISFIED);
      auto* r_reached1 = new State("R reached", Verdict::VIOLATED);
      auto* r_reached2 = new State("R reached", Verdict::SATISFIED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, p_holds, 1.0, EVENT_P);
      auto* t2 = new AllRequiredEventsInactiveTransition(p_holds, initial_state, 1.0, EVENT_P | EVENT_R);
      auto* t3 = new AllRequiredEventsActiveTransition(initial_state, r_reached1, 1.0, EVENT_R);
      auto* t4 = new AllRequiredEventsActiveTransition(p_holds, r_reached2, 1.0, EVENT_R);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_holds);
      this->addState(r_reached1);
      this->addState(r_reached2);
    }
};
#endif