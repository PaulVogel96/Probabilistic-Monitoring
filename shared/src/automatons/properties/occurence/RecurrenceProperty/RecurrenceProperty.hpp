#ifndef RecurrenceProperty_hpp
#define RecurrenceProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"P holds repeatedly"
class RecurrenceProperty : public ProbStatemachine {
  public:
    RecurrenceProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::VIOLATED);
      static State<ProbTransition> p_has_happened("P happened", Verdict::SATISFIED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &p_has_happened, 1.0, EVENT_P);
      static AllRequiredEventsInactiveTransition t2(&p_has_happened, &initial_state, 1.0, EVENT_P);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&p_has_happened);
    }
};
#endif