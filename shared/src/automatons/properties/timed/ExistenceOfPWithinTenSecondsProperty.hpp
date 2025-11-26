#ifndef ExistenceOfPWithinTenSecondsProperty_hpp
#define ExistenceOfPWithinTenSecondsProperty_hpp

#include "../../../State.hpp"
#include "../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/untimed/AllRequiredEventsInactiveTransition.hpp"
#include "../../../transitions/timed/TimedAllrequiredEventsInactiveTransition.hpp"
#include "../../../transitions/timed/Predicates.hpp"
#include "../../../ProbStatemachine.hpp"

//"It is eventually the case that P holds"
class ExistenceOfPWithinTenSecondsProperty : public ProbStatemachine {
  public:
    ExistenceOfPWithinTenSecondsProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::VIOLATED);
      auto* p_holds = new State("P happened", Verdict::SATISFIED);

      auto* p_has_happened = new AllRequiredEventsActiveTransition(initial_state, p_holds, 1.0, EVENT_P);
      auto* p_did_not_happen = new TimedAllRequiredEventsInactiveTransition(p_holds, initial_state, 1.0, EVENT_P, pred_P_did_not_happen_for_10s);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_holds);
    }
};
#endif