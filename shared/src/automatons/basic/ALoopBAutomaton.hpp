#ifndef TwoStateLoopAutomaton_hpp
#define TwoStateLoopAutomaton_hpp

#include "../../State.hpp"
#include "../../ProbTransition.hpp"
#include "../../ProbStatemachine.hpp"
#include "../../Events.hpp"
#include "../../transitions/untimed/ExactEventsActiveTransition.hpp"

class ALoopBAutomaton : public ProbStatemachine {
  public:
    ALoopBAutomaton() : ProbStatemachine() {
      auto* a = new State("A", Verdict::INCONCLUSIVE);
      auto* b = new State("B", Verdict::SATISFIED);

      auto* t1 = new ExactEventsActiveTransition(a, b, 0.5, EVENT_P);
      auto* t2 = new ExactEventsActiveTransition(a, a, 0.5, EVENT_P);

      this->initialState = this->addState(a);
      this->states[this->initialState] = 1;
      this->addState(b);
    }
};
#endif 