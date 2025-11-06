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
      static State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
      static State<ProbTransition> b("B", Verdict::INCONCLUSIVE);
      static State<ProbTransition> c("C", Verdict::INCONCLUSIVE);
      static State<ProbTransition> d("D", Verdict::SATISFIED);
      static State<ProbTransition> e("E", Verdict::VIOLATED);
      static State<ProbTransition> f("F", Verdict::SATISFIED);
      static State<ProbTransition> g("G", Verdict::VIOLATED);

      static ExactEventsActiveTransition t1(&a, &b, 0.3, EVENT_P);
      static ExactEventsActiveTransition t2(&a, &c, 0.5, EVENT_P);
      static ExactEventsActiveTransition t3(&a, &a, 0.2, EVENT_P);
      static ExactEventsActiveTransition t4(&b, &d, 0.4, EVENT_Q);
      static ExactEventsActiveTransition t5(&b, &e, 0.6, EVENT_Q);
      static ExactEventsActiveTransition t6(&c, &f, 0.8, EVENT_R);
      static ExactEventsActiveTransition t7(&c, &g, 0.2, EVENT_R);

      this->initialState = this->addState(&a);
      this->states[this->initialState] = 1;

      this->addState(&b);
      this->addState(&c);
      this->addState(&d);
      this->addState(&e);
      this->addState(&f);
      this->addState(&g);
    }
};
#endif