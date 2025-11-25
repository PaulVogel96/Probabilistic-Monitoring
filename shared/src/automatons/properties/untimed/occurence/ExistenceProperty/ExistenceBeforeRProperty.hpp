#ifndef ExistenceBeforeRProperty_hpp
#define ExistenceBeforeRProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"Before R holds, it is eventually the case that P holds"
class ExistenceBeforeRProperty : public ProbStatemachine {
  public:
    ExistenceBeforeRProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::INCONCLUSIVE);
      auto* p_has_happened = new State("P happened", Verdict::SATISFIED);
      auto* r_has_happened_without_p = new State("R before P", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, p_has_happened, 1.0, EVENT_P);
      auto* t2 = new AllRequiredEventsInactiveTransition(initial_state, p_has_happened, 1.0, EVENT_P);
      auto* t3 = new AllRequiredEventsActiveTransition(initial_state, r_has_happened_without_p, 1.0, EVENT_R);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_has_happened);
      this->addState(r_has_happened_without_p);
    }
};
#endif