#ifndef PrecedenceBetweenQAndRProperty_hpp
#define PrecedenceBetweenQAndRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../transitions/AnyRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/MixedEventsConditionTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"Between Q holds and R holds, if P holds then it must be that case that S holds before P"
class PrecedenceBetweenQAndRProperty : public ProbStatemachine {
  public:
    PrecedenceBetweenQAndRProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::VIOLATED);
      static State<ProbTransition> not_p_nor_s("Neither P nor S happened", Verdict::VIOLATED);
      static State<ProbTransition> s_happened("S happened", Verdict::SATISFIED);
      static State<ProbTransition> p_before_s("P happened before S", Verdict::INCONCLUSIVE);
      static State<ProbTransition> error("Error", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_happened, 1.0, EVENT_Q);
      static AllRequiredEventsActiveTransition t2(&q_happened, &initial_state, 1.0, EVENT_R);
      static MixedEventConditionTransition t3(&q_happened, &s_happened, 1.0, EVENT_S, EVENT_R);
      static AllRequiredEventsInactiveTransition t4(&q_happened, &not_p_nor_s, 1.0, EVENT_P | EVENT_R | EVENT_R);
      static AllRequiredEventsActiveTransition t5(&not_p_nor_s, &p_before_s, 1.0, EVENT_P);
      static AnyRequiredEventsActiveTransition t6(&p_before_s, &error, 1.0, EVENT_R | EVENT_S);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&q_happened);
      this->addState(&not_p_nor_s);
      this->addState(&s_happened);
      this->addState(&p_before_s);
      this->addState(&error);
    }
};
#endif