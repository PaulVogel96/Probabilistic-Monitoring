#ifndef RecurrenceOfPWithinTwentySecondsProperty_hpp
#define RecurrenceOfPWithinTwentySecondsProperty_hpp

#include "../../../State.hpp"
#include "../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/timed/TimedMatchEverythingTransition.hpp"
#include "../../../transitions/timed/predicates/TimePredicateWrapper.hpp"
#include "../../../ProbStatemachine.hpp"

//"very sliding window of length 20 s contains at least one p"
class RecurrenceOfPWithinTwentySecondsProperty : public ProbStatemachine {
  public:
    RecurrenceOfPWithinTwentySecondsProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::INCONCLUSIVE);
      auto* p_did_not_hold = new State("P did not hold in a 20s window", Verdict::VIOLATED);
      
      TimePredicateWrapper* pred_20s_no_p = new TimePredicateWrapper{TimePredicate{EVENT_P, TimeComparator::GREATER, 20000}};
      auto* p_did_not_hold_transition = new TimedMatchEverythingTransition(initial_state, p_did_not_hold, 1.0, pred_20s_no_p);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_did_not_hold);
    }
};


#endif