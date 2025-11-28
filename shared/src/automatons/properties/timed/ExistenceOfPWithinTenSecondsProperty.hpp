#ifndef ExistenceOfPWithinTenSecondsProperty_hpp
#define ExistenceOfPWithinTenSecondsProperty_hpp

#include "../../../State.hpp"
#include "../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/timed/TimedAllrequiredEventsInactiveTransition.hpp"
#include "../../../transitions/timed/predicates/TimePredicateWrapper.hpp"
#include "../../../ProbStatemachine.hpp"

//"At least one p within ≤ 10 s"
class ExistenceOfPWithinTenSecondsProperty : public ProbStatemachine {
  public:
    ExistenceOfPWithinTenSecondsProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::VIOLATED);
      auto* p_holds = new State("P happened", Verdict::SATISFIED);

      TimePredicateWrapper* pred_10s_no_p = new TimePredicateWrapper{TimePredicate{EVENT_P, TimeComparator::GREATER, 10000}};

      auto* p_has_happened = new AllRequiredEventsActiveTransition(initial_state, p_holds, 1.0, EVENT_P);
      auto* p_did_not_happen = new TimedAllRequiredEventsInactiveTransition(p_holds, initial_state, 1.0, EVENT_P, pred_10s_no_p);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_holds);
    }
};
#endif