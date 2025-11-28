#ifndef RecurrenceOfPWithinTwentySecondsProperty_hpp
#define RecurrenceOfPWithinTwentySecondsProperty_hpp

#include "../../../State.hpp"
#include "../../../transitions/timed/TimedAllRequiredEventsInactiveTransition.hpp"
#include "../../../transitions/timed/predicates/TimePredicateWrapper.hpp"
#include "../../../ProbStatemachine.hpp"

//"After x, y remains true over 0–6 s"
class RecurrenceOfPWithinTwentySecondsProperty : public ProbStatemachine {
  public:
    RecurrenceOfPWithinTwentySecondsProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* p_did_not_hold = new State("P did not hold in a 20s window", Verdict::VIOLATED);
      
      TimePredicateWrapper* pred_20s_no_p = new TimePredicateWrapper{TimePredicate{EVENT_P, TimeComparator::GREATER, 20000}};

      auto* p_did_not_hold_transition = new TimedAllRequiredEventsInactiveTransition(initial_state, p_did_not_hold, 1.0, EVENT_P, pred_20s_no_p);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
    }
};


#endif