#ifndef UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty_hpp
#define UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/untimed/MixedEventsConditionTransition.hpp"
#include "../../../../transitions/timed/TimedAllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/timed/TimedAllRequiredEventsInactiveTransition.hpp"
#include "../../../../transitions/timed/TimedNotAllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/timed/TimedMatchEverythingTransition.hpp"
#include "../../../../transitions/timed/predicates/TimePredicateWrapper.hpp"
#include "../../../../ProbStatemachine.hpp"

//"After each r, s must hold continuously at the three samples {r, r+1, r+2}"
class UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty : public ProbStatemachine {
  public:
    UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty() : ProbStatemachine() {      
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* r_held = new State("R Held", Verdict::INCONCLUSIVE);
      auto* s_did_not_hold = new State("S did not hold after R", Verdict::VIOLATED);

      TimePredicateWrapper* predicate_time_during_window =  new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 2000}};
      TimePredicateWrapper* predicate_time_at_2000ms = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::EQUAL, 2000}};
      TimePredicateWrapper* predicate_time_window_over = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::GREATER, 2000}};

      new AllRequiredEventsActiveTransition(initial_state, r_held, 1.0, EVENT_R | EVENT_S);
      new MixedEventsConditionTransition(initial_state, s_did_not_hold, 1.0, EVENT_R, EVENT_S);
      new TimedAllRequiredEventsInactiveTransition(r_held, s_did_not_hold, 1.0, EVENT_S, predicate_time_during_window);
      new TimedAllRequiredEventsInactiveTransition(r_held, s_did_not_hold, 1.0, EVENT_S, predicate_time_at_2000ms);
      new TimedAllRequiredEventsActiveTransition(r_held, initial_state, 1.0, EVENT_S, predicate_time_at_2000ms);
      new TimedMatchEverythingTransition(r_held, initial_state, 1.0, predicate_time_window_over);
      new TimedNotAllRequiredEventsActiveTransition(s_did_not_hold, initial_state, 1.0, EVENT_R | EVENT_S, predicate_time_window_over);
      new AllRequiredEventsActiveTransition(s_did_not_hold, r_held, 1.0, EVENT_R | EVENT_S);

      //additiona probabilistic transitions
      float globalProbR = 0.0896f;
      float globalProbS = 0.2839f;

      //assuming independence of s and r being activetogether on missing ticks
      float p_missing_RS = globalProbR * globalProbS;
      float p_missing_R_notS  = globalProbR * (1.0f - globalProbS);

      new AllRequiredEventsActiveTransition(initial_state, r_held, p_missing_RS, EVENTS_MISSING);
      new AllRequiredEventsActiveTransition(initial_state, s_did_not_hold, p_missing_R_notS, EVENTS_MISSING);
      new TimedAllRequiredEventsActiveTransition(r_held, s_did_not_hold, 1 - globalProbS, EVENTS_MISSING, predicate_time_during_window);
      new TimedAllRequiredEventsActiveTransition(r_held, s_did_not_hold, 1 - globalProbS, EVENTS_MISSING, predicate_time_at_2000ms);
      new TimedAllRequiredEventsActiveTransition(r_held, initial_state, globalProbS, EVENTS_MISSING, predicate_time_at_2000ms);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(r_held);
      this->addState(s_did_not_hold);
    }
};
#endif