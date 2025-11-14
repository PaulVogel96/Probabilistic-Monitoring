#ifndef PrecedenceBeforeRProperty_hpp
#define PrecedenceBeforeRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"Before R holds, if P holds then it must be that case that S holds before P"
class PrecedenceBeforeRProperty : public ProbStatemachine {
  public:
    PrecedenceBeforeRProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> before_p("S or R happened before P", Verdict::SATISFIED);
      static State<ProbTransition> p_happened("S happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> after_p("S or R happened after P", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &before_p, 1.0, EVENT_S);
      static AllRequiredEventsActiveTransition t2(&initial_state, &before_p, 1.0, EVENT_R);
      static AllRequiredEventsActiveTransition t3(&initial_state, &p_happened, 1.0, EVENT_P);
      static AllRequiredEventsActiveTransition t4(&p_happened, &after_p, 1.0, EVENT_R);
      static AllRequiredEventsActiveTransition t5(&p_happened, &after_p, 1.0, EVENT_S);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&before_p);
      this->addState(&p_happened);
      this->addState(&after_p);
    }
};
#endif