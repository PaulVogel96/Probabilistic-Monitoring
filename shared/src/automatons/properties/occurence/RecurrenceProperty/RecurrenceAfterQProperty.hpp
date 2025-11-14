#ifndef RecurrenceAfterQProperty_hpp
#define RecurrenceAfterQProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"After Q holds, P holds repeatedly"
class RecurrenceAfterQProperty : public ProbStatemachine {
  public:
    RecurrenceAfterQProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> q_happened("Q happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_happened("P happened", Verdict::SATISFIED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_happened, 1.0, EVENT_Q);
      static AllRequiredEventsActiveTransition t2(&q_happened, &p_happened, 1.0, EVENT_P);
      static AllRequiredEventsInactiveTransition t3(&p_happened, &q_happened, 1.0, EVENT_P);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&p_happened);
      this->addState(&q_happened);
    }
};
#endif