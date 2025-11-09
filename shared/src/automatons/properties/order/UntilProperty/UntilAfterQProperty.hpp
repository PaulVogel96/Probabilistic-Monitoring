#ifndef UntilAfterQProperty_hpp
#define UntilAfterQProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"P holds without interruption until S holds after Q holds
class UntilAfterQProperty : public ProbStatemachine {
  public:
    UntilAfterQProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_holds("Q", Verdict::INCONCLUSIVE);
      static State<ProbTransition> s_holds("S", Verdict::SATISFIED);
      static State<ProbTransition> error("Error State", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_holds, 1.00, EVENT_Q);
      static AllRequiredEventsActiveTransition t2(&q_holds, &s_holds, 1.00, EVENT_S);
      static AllRequiredEventsInactiveTransition t3(&q_holds, &error, 1.0, EVENT_P | EVENT_S);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&q_holds);
      this->addState(&s_holds);
      this->addState(&error);
    }
};
#endif