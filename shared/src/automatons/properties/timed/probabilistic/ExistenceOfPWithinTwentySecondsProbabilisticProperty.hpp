#ifndef ExistenceOfPWithinTwentySecondsProbabilisticProperty_hpp
#define ExistenceOfPWithinTwentySecondsProbabilisticProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/timed/TimedAllrequiredEventsInactiveTransition.hpp"
#include "../../../../transitions/timed/predicates/TimePredicateWrapper.hpp"
#include "../../../../ProbStatemachine.hpp"

//"very sliding window of length 20 s contains at least one p"
class ExistenceOfPWithinTwentySecondsProbabilisticProperty : public ProbStatemachine {
  public:
    ExistenceOfPWithinTwentySecondsProbabilisticProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::VIOLATED);
      auto* p_holds = new State("P happened", Verdict::SATISFIED);

      TimePredicateWrapper* pred_20s_no_p = new TimePredicateWrapper{TimePredicate{EVENT_P, TimeComparator::GREATER, 20000}};

      auto* p_has_happened = new AllRequiredEventsActiveTransition(initial_state, p_holds, 1.0, EVENT_P);
      auto* p_did_not_happen = new TimedAllRequiredEventsInactiveTransition(p_holds, initial_state, 1.0, EVENT_P, pred_20s_no_p);
      auto* interpret_missing_with_probability = new AllRequiredEventsActiveTransition(initial_state, p_holds, 0.0921, EVENTS_MISSING);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_holds);
    }
};
#endif