#ifndef ExistenceProperty_hpp
#define ExistenceProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"It is eventually the case that P holds"
class ExistenceProperty : public ProbStatemachine {
  public:
    ExistenceProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::INCONCLUSIVE);
      auto* p_has_happened = new State("P happened", Verdict::SATISFIED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, p_has_happened, 1.0, EVENT_P);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_has_happened);
    }
};
#endif