#ifndef UniversalityProperty_hpp
#define UniversalityProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/ExactEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"It is always the case that P holds"
class UniversalityProperty : public ProbStatemachine {
  public:
    UniversalityProperty() : ProbStatemachine() {
      static State<ProbTransition> p("P", Verdict::SATISFIED);
      static State<ProbTransition> not_p("NOT_P", Verdict::VIOLATED);

      static ExactEventsInactiveTransition t1(&p, &not_p, 1.0, EVENT_P);

      this->initialState = this->addState(&p);
      this->states[this->initialState] = 1;
      this->addState(&not_p);
    }
};
#endif