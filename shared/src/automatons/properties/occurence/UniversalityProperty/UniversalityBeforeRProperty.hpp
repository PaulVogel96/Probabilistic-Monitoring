#ifndef UniversalityBeforeRProperty_hpp
#define UniversalityBeforeRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../transitions/MixedEventsConditionTransition.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/ExactEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"Before R, it is always the case that P holds"
class UniversalityBeforeRProperty : public ProbStatemachine {
  public:
    UniversalityBeforeRProperty() : ProbStatemachine() {
      auto* initial_state = new State<ProbTransition>("Initial State", Verdict::INCONCLUSIVE);
      auto* p_holds = new State<ProbTransition>("P holds", Verdict::INCONCLUSIVE);
      auto* r_holds = new State<ProbTransition>("R holds", Verdict::SATISFIED);
      auto* not_p_or_r = new State<ProbTransition>("Not P or R holds", Verdict::INCONCLUSIVE);
      auto* r_after_not_p = new State<ProbTransition>("R happened after not P", Verdict::VIOLATED);

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