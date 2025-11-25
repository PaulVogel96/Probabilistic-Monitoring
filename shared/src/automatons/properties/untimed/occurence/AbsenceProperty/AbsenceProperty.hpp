#ifndef AbsenceProperty_hpp
#define AbsenceProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"Globally, It is never the case that P holds"
class AbsenceProperty : public ProbStatemachine {
  public:
    AbsenceProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* p_holds = new State("P happened", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, p_holds, 1.0, EVENT_P);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_holds);
    }
};
#endif