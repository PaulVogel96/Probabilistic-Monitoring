#ifndef UniversalityOfSAfterRWithinThreeSecondsProperty_hpp
#define UniversalityOfSAfterRWithinThreeSecondsProperty_hpp

#include "../../../State.hpp"
#include "../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/timed/TimedAllRequiredEventsInactiveTransition.hpp"
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

      new AllRequiredEventsActiveTransition(initial_state, r_held, 1.0, EVENT_R);
      new TimedAllRequiredEventsInactiveTransition(r_held, s_did_not_hold, 1.0, EVENT_S, 
        new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS_EQUAL, 2000}}
      );
      new TimedMatchEverythingTransition(r_held, initial_state, 1.0, 
        new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::GREATER, 2000}}
      );
      new AllRequiredEventsActiveTransition(s_did_not_hold, r_held, 1.0, EVENT_R);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(r_held);
      this->addState(s_did_not_hold);
    }
};
#endif