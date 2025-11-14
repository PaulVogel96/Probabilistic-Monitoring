#ifndef ExistenceProperty_hpp
#define ExistenceProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"It is eventually the case that P holds"
class ExistenceProperty : public ProbStatemachine {
  public:
    ExistenceProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_has_happened("P happened", Verdict::SATISFIED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &initial_state, 1.0, EVENT_P);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&p_has_happened);
    }
};
#endif