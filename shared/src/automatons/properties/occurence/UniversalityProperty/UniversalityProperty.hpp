#ifndef UniversalityProperty_hpp
#define UniversalityProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/ExactEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"It is always the case that P holds"
class UniversalityProperty : public ProbStatemachine {
  public:
    UniversalityProperty() : ProbStatemachine() {
      auto* p_holds = new State<ProbTransition>("P", Verdict::SATISFIED);
      auto* not_p_holds = new State<ProbTransition>("NOT_P", Verdict::VIOLATED);

      auto* t1 = new ExactEventsInactiveTransition(p_holds, not_p_holds, 1.0, EVENT_P);

      this->initialState = this->addState(p_holds);
      this->states[this->initialState] = 1;
      this->addState(not_p_holds);
    }
};
#endif