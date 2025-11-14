#ifndef ResponseAfterQProperty_hpp
#define ResponseAfterQProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//After Q, if P happens, then in response S eventually holds
class ResponseAfterQProperty : public ProbStatemachine {
  public:
    ResponseAfterQProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::SATISFIED);
      static State<ProbTransition> p_happened("P happened", Verdict::INCONCLUSIVE);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_happened, 1.0, EVENT_Q);
      static AllRequiredEventsActiveTransition t2(&q_happened, &p_happened, 1.0, EVENT_P);
      static AllRequiredEventsActiveTransition t3(&p_happened, &q_happened, 1.0, EVENT_S);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&q_happened);
      this->addState(&p_happened);
    }
};
#endif