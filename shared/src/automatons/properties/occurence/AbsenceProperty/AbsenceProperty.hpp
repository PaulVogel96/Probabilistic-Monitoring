#ifndef AbsenceProperty_hpp
#define AbsenceProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"Globally, It is never the case that P holds"
class AbsenceProperty : public ProbStatemachine {
  public:
    AbsenceProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> p_holds("P happened", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &p_holds, 1.0, EVENT_P);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&p_holds);
    }
};
#endif