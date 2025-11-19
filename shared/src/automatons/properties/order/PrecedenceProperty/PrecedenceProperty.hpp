#ifndef PrecedenceProperty_hpp
#define PrecedenceProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"


//"If P holds then it must be that case that S holds before P"
class PrecedenceProperty : public ProbStatemachine {
  public:
    PrecedenceProperty() : ProbStatemachine() {
      auto* initial_state = new State<ProbTransition>("Initial State", Verdict::INCONCLUSIVE);
      auto* p_happened = new State<ProbTransition>("P happened before S", Verdict::VIOLATED);
      auto* s_happened = new State<ProbTransition>("S happened", Verdict::SATISFIED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, p_happened, 1.0, EVENT_P);
      auto* t2 = new AllRequiredEventsActiveTransition(initial_state, s_happened, 1.0, EVENT_S);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_happened);
      this->addState(s_happened);
    }
};
#endif