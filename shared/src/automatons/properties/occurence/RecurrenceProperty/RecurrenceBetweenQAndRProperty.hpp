#ifndef RecurrenceBetweenQAndRProperty_hpp
#define RecurrenceBetweenQAndRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"Between Q and R, P holds repeatedly"
class RecurrenceBetweenQAndRProperty : public ProbStatemachine {
  public:
    RecurrenceBetweenQAndRProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> q_happened("Q happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_happened("Q happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> not_p_happened("P did not happen", Verdict::INCONCLUSIVE);
      static State<ProbTransition> r_happened("P did not happen", Verdict::SATISFIED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_happened, 1.0, EVENT_Q);
      static AllRequiredEventsActiveTransition t2(&q_happened, &r_happened, 1.0, EVENT_R);
      static AllRequiredEventsActiveTransition t3(&q_happened, &p_happened, 1.0, EVENT_P);
      static AllRequiredEventsInactiveTransition t4(&p_happened, &not_p_happened, 1.0, EVENT_P | EVENT_R);
      static AllRequiredEventsActiveTransition t5(&not_p_happened, &r_happened, 1.0, EVENT_R);
      static AllRequiredEventsActiveTransition t6(&p_happened, &r_happened, 1.0, EVENT_R);
      static AllRequiredEventsActiveTransition t7(&r_happened, &q_happened, 1.0, EVENT_R);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&q_happened);
      this->addState(&p_happened);
      this->addState(&not_p_happened);
      this->addState(&r_happened);
    }
};
#endif