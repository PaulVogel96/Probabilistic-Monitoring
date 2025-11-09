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
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_holds("P holds", Verdict::INCONCLUSIVE);
      static State<ProbTransition> r_holds("R holds", Verdict::SATISFIED);
      static State<ProbTransition> not_p_or_r("Not P or R holds", Verdict::INCONCLUSIVE);
      static State<ProbTransition> r_after_not_p("R happened after not P", Verdict::VIOLATED);

      static AllRequiredEventsInactiveTransition t1(&initial_state, &not_p_or_r, 1.0, EVENT_P | EVENT_R);
      static MixedEventConditionTransition t2(&initial_state, &p_holds, 1.0, EVENT_P, EVENT_R);
      static AllRequiredEventsActiveTransition t3(&initial_state, &r_holds, 1.0, EVENT_R);
      static AllRequiredEventsActiveTransition t4(&p_holds, &r_holds, 1.0, EVENT_R);
      static ExactEventsInactiveTransition t5(&p_holds, &not_p_or_r, 1.0, EVENT_P);
      static AllRequiredEventsActiveTransition t6(&not_p_or_r, &r_after_not_p, 1.0, EVENT_R);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&p_holds);
      this->addState(&r_holds);
      this->addState(&not_p_or_r);
      this->addState(&r_after_not_p);
    }
};
#endif