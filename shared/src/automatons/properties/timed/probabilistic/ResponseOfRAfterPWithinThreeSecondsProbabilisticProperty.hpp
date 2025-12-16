#ifndef ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty_hpp
#define ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/timed/TimedAllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/timed/TimedAllRequiredEventsInactiveTransition.hpp"
#include "../../../../transitions/timed/TimedMatchEverythingTransition.hpp"
#include "../../../../transitions/timed/predicates/TimePredicateWrapper.hpp"
#include "../../../../ProbStatemachine.hpp"

//"After each p, an r must occur within [p+1, p+3]"
class ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty : public ProbStatemachine {
  public:
    ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* p_held = new State("P Held", Verdict::INCONCLUSIVE);
      auto* r_did_not_hold = new State("R did not hold after P", Verdict::VIOLATED);

      TimePredicateWrapper* time_within_window = new TimePredicateWrapper{TimePredicate{EVENT_P, TimeComparator::BETWEEN, 1000, 3000}};
      TimePredicateWrapper* time_after_window = new TimePredicateWrapper{TimePredicate{EVENT_P, TimeComparator::GREATER, 3000}};

      new AllRequiredEventsActiveTransition(initial_state, p_held, 1.0, EVENT_P);
      new TimedAllRequiredEventsActiveTransition(p_held, initial_state, 1.0, EVENT_R, time_within_window);
      new TimedAllRequiredEventsInactiveTransition(p_held, r_did_not_hold, 1.0, EVENT_R, time_after_window);
      new AllRequiredEventsActiveTransition(r_did_not_hold, p_held, 1.0, EVENT_P);

      //additional probabilistic transitions
      float globalProbP = 0.0921f;
      float globalProbR = 0.0896f;
      
      auto* missing_as_p = new AllRequiredEventsActiveTransition(initial_state, p_held, globalProbP, EVENTS_MISSING);
      auto* missing_as_r_success = new TimedAllRequiredEventsActiveTransition(p_held, initial_state, globalProbR, EVENTS_MISSING, time_within_window);
      auto* missing_timeout_violation = new TimedAllRequiredEventsActiveTransition(p_held, r_did_not_hold, globalProbR, EVENTS_MISSING, time_after_window);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_held);
      this->addState(r_did_not_hold);
  }
};
#endif