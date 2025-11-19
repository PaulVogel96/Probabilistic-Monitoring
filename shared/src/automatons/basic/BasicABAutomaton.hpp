#ifndef BasicABAutomaton_hpp
#define BasicABAutomaton_hpp

#include "../../State.hpp"
#include "../../ProbTransition.hpp"
#include "../../ProbStatemachine.hpp"
#include "../../Events.hpp"
#include "../../transitions/ExactEventsActiveTransition.hpp"

class BasicABAutomaton : public ProbStatemachine {
  public:
    BasicABAutomaton() : ProbStatemachine() {
      auto* a = new State("A", Verdict::INCONCLUSIVE);
      auto* b = new State("B", Verdict::SATISFIED);

      auto* t1 = new ExactEventsActiveTransition(a, b, 1.0, EVENT_P);

      this->initialState = this->addState(a);
      this->states[this->initialState] = 1;
      this->addState(b);
    }
};
#endif