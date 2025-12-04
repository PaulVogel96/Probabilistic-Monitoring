#ifndef ResponseOfRAfterPWithinThreeSecondsProperty_hpp
#define ResponseOfRAfterPWithinThreeSecondsProperty_hpp

#include "../../../State.hpp"
#include "../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/timed/TimedAllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/timed/TimedAllRequiredEventsInactiveTransition.hpp"
#include "../../../transitions/timed/TimedMatchEverythingTransition.hpp"
#include "../../../transitions/timed/predicates/TimePredicateWrapper.hpp"
#include "../../../ProbStatemachine.hpp"

//"After each p, an r must occur within [p+1, p+3]"
class ResponseOfRAfterPWithinThreeSecondsProperty : public ProbStatemachine {
  public:
    ResponseOfRAfterPWithinThreeSecondsProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* p_held = new State("P Held", Verdict::INCONCLUSIVE);
      auto* r_did_not_hold = new State("R did not hold after P", Verdict::VIOLATED);

      auto* p_happened = new AllRequiredEventsActiveTransition(initial_state, p_held, 1.0, EVENT_P);

      auto* success = new TimedAllRequiredEventsActiveTransition(p_held, initial_state, 1.0, EVENT_R,
          new TimePredicateWrapper{ TimePredicate{EVENT_P, TimeComparator::BETWEEN, 1000, 3000} }
      );

      auto* violation = new TimedAllRequiredEventsInactiveTransition(p_held, r_did_not_hold, 1.0, EVENT_R,
         new TimePredicateWrapper{ TimePredicate{EVENT_P, TimeComparator::GREATER, 3000}}
      );
      auto* p_again = new AllRequiredEventsActiveTransition(r_did_not_hold, p_held, 1.0, EVENT_P);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_held);
      this->addState(r_did_not_hold);
    }
};
#endif