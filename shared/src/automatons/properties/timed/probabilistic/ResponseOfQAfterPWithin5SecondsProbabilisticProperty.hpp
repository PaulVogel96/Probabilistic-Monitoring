#ifndef ResponseOfQAfterPWithinFiveSecondsProbabilisticProperty_hpp
#define ResponseOfQAfterPWithinFiveSecondsProbabilisticProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/timed/TimedAllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/timed/TimedAllRequiredEventsInactiveTransition.hpp"
#include "../../../../transitions/timed/TimedMatchEverythingTransition.hpp"
#include "../../../../transitions/timed/predicates/TimePredicateWrapper.hpp"
#include "../../../../ProbStatemachine.hpp"

//"After each p, an q must occur within [p+1, p+5]"
class ResponseOfQAfterPWithinFiveSecondsProbabilisticProperty : public ProbStatemachine {
  public:
    ResponseOfQAfterPWithinFiveSecondsProbabilisticProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* p_held = new State("P Held", Verdict::INCONCLUSIVE);
      auto* q_did_not_hold = new State("Q did not hold after P", Verdict::VIOLATED);

      TimePredicateWrapper* time_within_window = new TimePredicateWrapper{TimePredicate{EVENT_P, TimeComparator::BETWEEN, 1000, 5000}};
      TimePredicateWrapper* time_after_window = new TimePredicateWrapper{TimePredicate{EVENT_P, TimeComparator::GREATER, 5000}};

      new AllRequiredEventsActiveTransition(initial_state, p_held, 1.0, EVENT_P);
      new TimedAllRequiredEventsActiveTransition(p_held, initial_state, 1.0, EVENT_Q, time_within_window);
      new TimedAllRequiredEventsInactiveTransition(p_held, q_did_not_hold, 1.0, EVENT_Q, time_after_window);
      new AllRequiredEventsActiveTransition(q_did_not_hold, p_held, 1.0, EVENT_P);

      //additional probabilistic transitions
      float globalProbP = 0.2;
      float globalProbQ = 0.1;
      
      auto* missing_as_p = new AllRequiredEventsActiveTransition(initial_state, p_held, globalProbP, EVENTS_MISSING);
      auto* missing_as_q_success = new TimedAllRequiredEventsActiveTransition(p_held, initial_state, globalProbQ, EVENTS_MISSING, time_within_window);
      auto* missing_timeout_violation = new TimedAllRequiredEventsActiveTransition(p_held, q_did_not_hold, 1 - globalProbQ, EVENTS_MISSING, time_after_window);
      auto* missing_timeout_satisfaction = new TimedAllRequiredEventsActiveTransition(p_held, initial_state, globalProbQ, EVENTS_MISSING, time_after_window);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_held);
      this->addState(q_did_not_hold);
  }
};
#endif