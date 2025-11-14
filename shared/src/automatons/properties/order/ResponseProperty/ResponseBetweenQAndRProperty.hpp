#ifndef ResponseBetweenQAndRProperty_hpp
#define ResponseBetweenQAndRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//Between Q and R, if P holds, in response S eventually holds
class ResponseBetweenQAndRProperty : public ProbStatemachine {
  public:
    ResponseBetweenQAndRProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::SATISFIED);
      static State<ProbTransition> p_happened("P happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> r_without_s("R happened before S did", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_happened, 1.0, EVENT_Q);
      static AllRequiredEventsActiveTransition t2(&q_happened, &initial_state, 1.0, EVENT_R);
      static AllRequiredEventsActiveTransition t3(&q_happened, &p_happened, 1.0, EVENT_P);
      static AllRequiredEventsActiveTransition t4(&p_happened, &initial_state, 1.0, EVENT_S);
      static AllRequiredEventsActiveTransition t5(&p_happened, &r_without_s, 1.0, EVENT_R);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&q_happened);
      this->addState(&p_happened);
      this->addState(&r_without_s);
    }
};
#endif