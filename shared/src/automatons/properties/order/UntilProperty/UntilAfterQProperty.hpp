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
      auto* initial_state = new State<ProbTransition>("Initial State", Verdict::SATISFIED);
      auto* q_holds = new State<ProbTransition>("Q", Verdict::INCONCLUSIVE);
      auto* s_holds = new State<ProbTransition>("S", Verdict::SATISFIED);
      auto* error = new State<ProbTransition>("Error State", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_holds, 1.00, EVENT_Q);
      auto* t2 = new AllRequiredEventsActiveTransition(q_holds, s_holds, 1.00, EVENT_S);
      auto* t3 = new AllRequiredEventsInactiveTransition(q_holds, error, 1.0, EVENT_P | EVENT_S);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(q_holds);
      this->addState(s_holds);
      this->addState(error);
    }
};
#endif