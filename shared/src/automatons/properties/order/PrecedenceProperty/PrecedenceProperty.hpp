#ifndef PrecedenceProperty_hpp
#define PrecedenceProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"


//"If P holds then it must be that case that S holds before P"
class PrecedenceProperty : public ProbStatemachine {
  public:
    PrecedenceProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_happened("P happened before S", Verdict::VIOLATED);
      static State<ProbTransition> s_happened("S happened", Verdict::SATISFIED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &p_happened, 1.0, EVENT_P);
      static AllRequiredEventsActiveTransition t2(&initial_state, &s_happened, 1.0, EVENT_S);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&p_happened);
      this->addState(&s_happened);
    }
};
#endif