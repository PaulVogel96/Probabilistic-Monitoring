#ifndef ExistenceOfSAfterRWithinFourSecondsProperty_hpp
#define ExistenceOfSAfterRWithinFourSecondsProperty_hpp

#include "../../../State.hpp"
#include "../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/timed/TimedAllrequiredEventsActiveTransition.hpp"
#include "../../../transitions/timed/TimedMatchEverythingTransition.hpp"
#include "../../../transitions/timed/Predicates.hpp"
#include "../../../ProbStatemachine.hpp"

//"After r, s occurs within 1–4 s"
class ExistenceOfSAfterRWithinFourSecondsProperty : public ProbStatemachine {
  public:
    ExistenceOfSAfterRWithinFourSecondsProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* r_holds = new State("R happened", Verdict::INCONCLUSIVE);
      auto* s_not_holds = new State("S did not happen in time", Verdict::VIOLATED);

      auto* r_has_happened = new AllRequiredEventsActiveTransition(initial_state, r_holds, 1.0, EVENT_R);
      auto* s_has_happened = new TimedAllRequiredEventsActiveTransition(r_holds, initial_state, 1.0, EVENT_S, pred_r_happened_less_or_equal_than_4s_ago);
      auto* s_has_not_happened = new TimedMatchEverythingTransition(r_holds, s_not_holds, 1.0, pred_r_happened_over_4s_ago);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(r_holds);
      this->addState(s_not_holds);
    }
};
#endif