#ifndef DoubleSplitAutomatonWithLoop_hpp
#define DoubleSplitAutomatonWithLoop_hpp

#include "../../State.hpp"
#include "../../ProbTransition.hpp"
#include "../../ProbStatemachine.hpp"
#include "../../Events.hpp"
#include "../../transitions/ExactEventsActiveTransition.hpp"

class DoubleSplitAutomatonWithLoop : public ProbStatemachine {
  public:
    DoubleSplitAutomatonWithLoop() : ProbStatemachine() {
      auto* a = new State<ProbTransition>("A", Verdict::INCONCLUSIVE);
      auto* b = new State<ProbTransition>("B", Verdict::INCONCLUSIVE);
      auto* c = new State<ProbTransition>("C", Verdict::INCONCLUSIVE);
      auto* d = new State<ProbTransition>("D", Verdict::SATISFIED);
      auto* e = new State<ProbTransition>("E", Verdict::VIOLATED);
      auto* f = new State<ProbTransition>("F", Verdict::SATISFIED);
      auto* g = new State<ProbTransition>("G", Verdict::VIOLATED);

      auto* t1 = new ExactEventsActiveTransition(a, b, 0.3, EVENT_P);
      auto* t2 = new ExactEventsActiveTransition(a, c, 0.5, EVENT_P);
      auto* t3 = new ExactEventsActiveTransition(a, a, 0.2, EVENT_P);
      auto* t4 = new ExactEventsActiveTransition(b, d, 0.4, EVENT_Q);
      auto* t5 = new ExactEventsActiveTransition(b, e, 0.6, EVENT_Q);
      auto* t6 = new ExactEventsActiveTransition(c, f, 0.8, EVENT_R);
      auto* t7 = new ExactEventsActiveTransition(c, g, 0.2, EVENT_R);

      this->initialState = this->addState(a);
      this->states[this->initialState] = 1;

      this->addState(b);
      this->addState(c);
      this->addState(d);
      this->addState(e);
      this->addState(f);
      this->addState(g);
    }
};
#endif