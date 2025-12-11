#ifndef ExistenceOfPWithinTwentySecondsProbabilisticProperty_hpp
#define ExistenceOfPWithinTwentySecondsProbabilisticProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/timed/TimedAllrequiredEventsInactiveTransition.hpp"
#include "../../../../transitions/timed/predicates/TimePredicateWrapper.hpp"
#include "../../../../ProbStatemachine.hpp"

//"every sliding window of length 20 s contains at least one p"
class ExistenceOfPWithinTwentySecondsProbabilisticProperty : public ProbStatemachine {
  public:
    ExistenceOfPWithinTwentySecondsProbabilisticProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::INCONCLUSIVE);
      auto* p_holds = new State("P happened", Verdict::SATISFIED);
      auto* p_did_not_hold = new State("P did not hold within 20s", Verdict::VIOLATED);

      TimePredicateWrapper* pred_20s_no_p = new TimePredicateWrapper{TimePredicate{EVENT_P, TimeComparator::GREATER, 20000}};
      
      new AllRequiredEventsActiveTransition(initial_state, p_holds, 1.0, EVENT_P);
      new TimedAllRequiredEventsInactiveTransition(p_holds, p_did_not_hold, 1.0, EVENT_P, pred_20s_no_p);
      new TimedAllRequiredEventsInactiveTransition(initial_state, p_did_not_hold, 1.0, EVENT_P, pred_20s_no_p);
      new AllRequiredEventsActiveTransition(initial_state, p_holds, 0.0921, EVENTS_MISSING); //interpret missing events as p with probability

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_holds);
    }
};
#endif