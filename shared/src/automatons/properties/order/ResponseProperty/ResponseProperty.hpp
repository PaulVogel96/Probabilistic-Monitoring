#ifndef ResponseProperty_hpp
#define ResponseProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"If P holds, then in response S eventually holds"
class ResponseProperty : public ProbStatemachine {
  public:
    ResponseProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> p_happened("P happened", Verdict::INCONCLUSIVE);
      static State<ProbTransition> s_happened("S happened", Verdict::SATISFIED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &p_happened, 1.0, EVENT_P);
      static AllRequiredEventsActiveTransition t2(&p_happened, &s_happened, 1.0, EVENT_S);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&p_happened);
      this->addState(&s_happened);
    }
};
#endif