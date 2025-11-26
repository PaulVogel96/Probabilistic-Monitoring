#ifndef RecurrenceProperty_hpp
#define RecurrenceProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../transitions/untimed/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"P holds repeatedly"
class RecurrenceProperty : public ProbStatemachine {
  public:
    RecurrenceProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::VIOLATED);
      auto* p_has_happened = new State("P happened", Verdict::SATISFIED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, p_has_happened, 1.0, EVENT_P);
      auto* t2 = new AllRequiredEventsInactiveTransition(p_has_happened, initial_state, 1.0, EVENT_P);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_has_happened);
    }
};
#endif