#ifndef AbsenceOfNAfterQWithinThreeSecondsProperty_hpp
#define AbsenceOfNAfterQWithinThreeSecondsProperty_hpp

#include "../../../State.hpp"
#include "../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/timed/TimedAllrequiredEventsActiveTransition.hpp"
#include "../../../transitions/timed/TimedMatchEverythingTransition.hpp"
#include "../../../transitions/timed/Predicates.hpp"
#include "../../../ProbStatemachine.hpp"

//"After q, n does not occur within ≤ 3 s"
class AbsenceOfNAfterQWithinThreeSecondsProperty : public ProbStatemachine {
  public:
    AbsenceOfNAfterQWithinThreeSecondsProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* q_holds = new State("Q happened", Verdict::INCONCLUSIVE);
      auto* n_holds = new State("N held in time", Verdict::VIOLATED);
      
      auto* q_has_happened = new AllRequiredEventsActiveTransition(initial_state, q_holds, 1.0, EVENT_Q);
      auto* n_did_not_happen = new TimedMatchEverythingTransition(q_holds, initial_state, 1.0, pred_q_happened_over_3s_ago);
      auto* n_did_happen = new TimedAllRequiredEventsActiveTransition(q_holds, n_holds, 1.0, EVENT_N, pred_q_happened_less_or_equal_than_3s_ago);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(q_holds);
      this->addState(n_holds);
    }
};
#endif