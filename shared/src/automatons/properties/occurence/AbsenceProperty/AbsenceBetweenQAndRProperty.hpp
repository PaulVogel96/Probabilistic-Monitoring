#ifndef AbsenceBetweenQAndRProperty_hpp
#define AbsenceBetweenQAndRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"It is never the case that P holds between Q and R"
class AbsenceBetweenQAndRProperty : public ProbStatemachine {
  public:
    AbsenceBetweenQAndRProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::SATISFIED);
      static State<ProbTransition> p_after_q("P happened after Q", Verdict::SATISFIED);
      static State<ProbTransition> r_after_q_and_p("R happened after Q and P", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_happened, 1.00, EVENT_Q);
      static AllRequiredEventsActiveTransition t2(&q_happened, &p_after_q, 1.00, EVENT_P);
      static AllRequiredEventsActiveTransition t3(&q_happened, &initial_state, 1.00, EVENT_R);
      static AllRequiredEventsActiveTransition t4(&p_after_q, &r_after_q_and_p, 1.00, EVENT_R);
      
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&q_happened);
      this->addState(&p_after_q);
      this->addState(&r_after_q_and_p);
    }
};
#endif