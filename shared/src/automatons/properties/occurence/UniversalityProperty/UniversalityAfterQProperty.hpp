#ifndef UniversalityAfterQProperty_hpp
#define UniversalityAfterQProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"After Q, it is always the case that P holds 
class UniversalityAfterQProperty : public ProbStatemachine {
  public:
    UniversalityAfterQProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::SATISFIED);
      static State<ProbTransition> not_p_happened_after_q("not P happened after Q", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_happened, 1.00, EVENT_Q);
      static AllRequiredEventsInactiveTransition t4(&q_happened, &not_p_happened_after_q, 1.00, EVENT_P);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&q_happened);
      this->addState(&not_p_happened_after_q);
    }
};
#endif