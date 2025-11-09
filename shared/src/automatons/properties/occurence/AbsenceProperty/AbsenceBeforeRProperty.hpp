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
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> r_has_happened("R happened", Verdict::SATISFIED);
      static State<ProbTransition> p_has_happened("P happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> r_after_p("R happened after P", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &r_has_happened, 1.0, EVENT_R);
      static MixedEventConditionTransition t2(&initial_state, &p_has_happened, 1.0, EVENT_P, EVENT_R);
      static AllRequiredEventsActiveTransition t3(&p_has_happened, &r_after_p, 1.0, EVENT_R);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&r_has_happened);
      this->addState(&p_has_happened);
      this->addState(&r_after_p);
    }
};
#endif