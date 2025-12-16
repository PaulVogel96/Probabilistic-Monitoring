#ifndef UniversalityOfSAfterRWithinThreeSecondsProperty_hpp
#define UniversalityOfSAfterRWithinThreeSecondsProperty_hpp

#include "../../../State.hpp"
#include "../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/untimed/MixedEventsConditionTransition.hpp"
#include "../../../transitions/timed/TimedAllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/timed/TimedAllRequiredEventsInactiveTransition.hpp"
#include "../../../transitions/timed/TimedNotAllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/timed/TimedMatchEverythingTransition.hpp"
#include "../../../transitions/timed/predicates/TimePredicateWrapper.hpp"
#include "../../../ProbStatemachine.hpp"

//"After each r, s must hold continuously at the three samples {r, r+1, r+2}"
class UniversalityOfSAfterRWithinThreeSecondsProperty : public ProbStatemachine {
  public:
    UniversalityOfSAfterRWithinThreeSecondsProperty() : ProbStatemachine() {
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

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(r_held);
      this->addState(s_did_not_hold);
    }
};
#endif