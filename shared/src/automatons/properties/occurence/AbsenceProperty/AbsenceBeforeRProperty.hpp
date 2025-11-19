#ifndef AbsenceBeforeRProperty_hpp
#define AbsenceBeforeRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../ProbStatemachine.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/MixedEventsConditionTransition.hpp"

//"It is never the case that P holds before R holds"
class AbsenceBeforeRProperty : public ProbStatemachine {
  public:
    AbsenceBeforeRProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::INCONCLUSIVE);
      auto* r_has_happened = new State("R happened", Verdict::SATISFIED);
      auto* p_has_happened = new State("P happened", Verdict::INCONCLUSIVE);
      auto* r_after_p = new State("R happened after P", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, r_has_happened, 1.0, EVENT_R);
      auto* t2 = new MixedEventsConditionTransition(initial_state, p_has_happened, 1.0, EVENT_P, EVENT_R);
      auto* t3 = new AllRequiredEventsActiveTransition(p_has_happened, r_after_p, 1.0, EVENT_R);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(r_has_happened);
      this->addState(p_has_happened);
      this->addState(r_after_p);
    }
};
#endif