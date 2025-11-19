#ifndef ExistenceBetweenQAndRProperty_hpp
#define ExistenceBetweenQAndRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"Between Q and R, it is eventually the case that P holds"
class ExistenceBetweenQAndRProperty : public ProbStatemachine {
  public:
    ExistenceBetweenQAndRProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_after_q("P happened after Q", Verdict::INCONCLUSIVE);
      static State<ProbTransition> not_p_or_r("Not P or R happened after Q", Verdict::INCONCLUSIVE);
      static State<ProbTransition> error("Error", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_happened, 1.0, EVENT_Q);
      static AllRequiredEventsActiveTransition t2(&q_happened, &initial_state, 1.00, EVENT_R);
      static AllRequiredEventsActiveTransition t3(&q_happened, &p_after_q, 1.0, EVENT_P);
      static AllRequiredEventsActiveTransition t4(&p_after_q, &initial_state, 1.0, EVENT_R);
      static AllRequiredEventsInactiveTransition t5(&q_happened, &not_p_or_r, 1.00, EVENT_P | EVENT_R);
      static AllRequiredEventsActiveTransition t6(&not_p_or_r, &p_after_q, 1.0, EVENT_P);
      static AllRequiredEventsActiveTransition t7(&not_p_or_r, &error, 1.0, EVENT_R);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&q_happened);
      this->addState(&p_after_q);
      this->addState(&not_p_or_r);
      this->addState(&error);
    }
};
#endif