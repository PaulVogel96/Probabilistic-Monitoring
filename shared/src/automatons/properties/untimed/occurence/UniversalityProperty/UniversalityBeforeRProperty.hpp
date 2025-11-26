#ifndef UniversalityBeforeRProperty_hpp
#define UniversalityBeforeRProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/untimed/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../../transitions/untimed/MixedEventsConditionTransition.hpp"
#include "../../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../transitions/untimed/ExactEventsInactiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"Before R, it is always the case that P holds"
class UniversalityBeforeRProperty : public ProbStatemachine {
  public:
    UniversalityBeforeRProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::INCONCLUSIVE);
      auto* p_holds = new State("P holds", Verdict::INCONCLUSIVE);
      auto* r_holds = new State("R holds", Verdict::SATISFIED);
      auto* not_p_or_r = new State("Not P or R holds", Verdict::INCONCLUSIVE);
      auto* r_after_not_p = new State("R happened after not P", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsInactiveTransition(initial_state, not_p_or_r, 1.0, EVENT_P | EVENT_R);
      auto* t2 = new MixedEventsConditionTransition(initial_state, p_holds, 1.0, EVENT_P, EVENT_R);
      auto* t3 = new AllRequiredEventsActiveTransition(initial_state, r_holds, 1.0, EVENT_R);
      auto* t4 = new MixedEventsConditionTransition(p_holds, r_holds, 1.0, EVENT_R, EVENT_P);
      auto* t5 = new AllRequiredEventsInactiveTransition(p_holds, not_p_or_r, 1.0, EVENT_P | EVENT_R);
      auto* t6 = new AllRequiredEventsActiveTransition(not_p_or_r, r_after_not_p, 1.0, EVENT_R);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_holds);
      this->addState(r_holds);
      this->addState(not_p_or_r);
      this->addState(r_after_not_p);
    }
};
#endif