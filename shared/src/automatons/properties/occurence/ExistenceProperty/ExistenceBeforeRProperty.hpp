#ifndef ExistenceBeforeRProperty_hpp
#define ExistenceBeforeRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"Before R holds, it is eventually the case that P holds"
class ExistenceBeforeRProperty : public ProbStatemachine {
  public:
    ExistenceBeforeRProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_has_happened("P happened", Verdict::SATISFIED);
      static State<ProbTransition> r_has_happened_without_p("R before P", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &p_has_happened, 1.0, EVENT_P);
      static AllRequiredEventsInactiveTransition t2(&initial_state, &p_has_happened, 1.0, EVENT_P);
      static AllRequiredEventsActiveTransition t3(&initial_state, &r_has_happened_without_p, 1.0, EVENT_R);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&p_has_happened);
      this->addState(&r_has_happened_without_p);
    }
};
#endif