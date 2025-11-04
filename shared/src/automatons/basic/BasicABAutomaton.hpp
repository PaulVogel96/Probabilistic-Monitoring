#ifndef BasicABAutomaton_hpp
#define BasicABAutomaton_hpp

#include "../../State.hpp"
#include "../../ProbTransition.hpp"
#include "../../ProbStatemachine.hpp"
#include "../../Events.hpp"
#include "../../transitions/ExactEventsMatchTransition.hpp"

class BasicABAutomaton : public ProbStatemachine {
  public:
    BasicABAutomaton() : ProbStatemachine() {
      static State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
      static State<ProbTransition> b("B", Verdict::SATISFIED);

      static ExactEventsMatchTransition t(&a, &b, 1.0, EVENT_P);

      this->initialState = this->addState(&a);
      this->states[this->initialState] = 1;

      this->addState(&b);
    }
};
#endif