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
      auto* initial_state = new State<ProbTransition>("Initial State", Verdict::INCONCLUSIVE);
      auto* q_happened = new State<ProbTransition>("Q happened", Verdict::INCONCLUSIVE);
      auto* p_happened = new State<ProbTransition>("P happened", Verdict::SATISFIED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_happened, 1.0, EVENT_Q);
      auto* t2 = new AllRequiredEventsActiveTransition(q_happened, p_happened, 1.0, EVENT_P);
      auto* t3 = new AllRequiredEventsInactiveTransition(p_happened, q_happened, 1.0, EVENT_P);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_happened);
      this->addState(q_happened);
    }
};
#endif