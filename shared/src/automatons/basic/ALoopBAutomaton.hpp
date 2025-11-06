#ifndef TwoStateLoopAutomaton_hpp
#define TwoStateLoopAutomaton_hpp

#include "../../State.hpp"
#include "../../ProbTransition.hpp"
#include "../../ProbStatemachine.hpp"
#include "../../Events.hpp"
#include "../../transitions/ExactEventsActiveTransition.hpp"

class ALoopBAutomaton : public ProbStatemachine {
  public:
    ALoopBAutomaton() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
      static State<ProbTransition> b("B", Verdict::SATISFIED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ExactEventsActiveTransition t1(&a, &b, 0.5, EVENT_P);
      static ExactEventsActiveTransition t2(&a, &a, 0.5, EVENT_P);

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&a);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&b);
    }
};
#endif 