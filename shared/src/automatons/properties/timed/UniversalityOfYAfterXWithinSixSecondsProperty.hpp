#ifndef UniversalityOfYAfterXWithinSixSecondsProperty_hpp
#define UniversalityOfYAfterXWithinSixSecondsProperty_hpp

#include "../../../State.hpp"
#include "../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/timed/TimedAllRequiredEventsInactiveTransition.hpp"
#include "../../../transitions/timed/TimedMatchEverythingTransition.hpp"
#include "../../../transitions/timed/Predicates.hpp"
#include "../../../ProbStatemachine.hpp"

//"After x, y remains true over 0–6 s"
class UniversalityOfYAfterXWithinSixSecondsProperty : public ProbStatemachine {
  public:
    UniversalityOfYAfterXWithinSixSecondsProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* x_holds = new State("X happened", Verdict::INCONCLUSIVE);
      auto* y_not_holds = new State("S did not happen in time", Verdict::VIOLATED);

      auto* r_has_happened = new AllRequiredEventsActiveTransition(initial_state, x_holds, 1.0, EVENT_X);
      auto* y_has_held = new TimedMatchEverythingTransition(x_holds, initial_state, 1.0, pred_x_happened_over_6s_ago);
      auto* y_has_not_held = new TimedAllRequiredEventsInactiveTransition(x_holds, y_not_holds, 1.0, EVENT_Y, pred_x_happened_less_or_equal_than_6s_ago);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(x_holds);
      this->addState(y_not_holds);
    }
};
#endif