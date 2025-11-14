#ifndef ResponseBeforeRProperty_hpp
#define ResponseBeforeRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"Before R holds, If P holds, then in response S eventually holds"
class ResponseBeforeRProperty : public ProbStatemachine {
  public:
    ResponseBeforeRProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> p_happened("P happened before S", Verdict::INCONCLUSIVE);
      static State<ProbTransition> r_after_p("R happened after P", Verdict::VIOLATED);
      static State<ProbTransition> r_without_p("R happened", Verdict::SATISFIED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &p_happened, 1.0, EVENT_P);
      static AllRequiredEventsActiveTransition t2(&p_happened, &initial_state, 1.0, EVENT_S);
      static AllRequiredEventsActiveTransition t3(&p_happened, &r_after_p, 1.0, EVENT_R);
      static AllRequiredEventsActiveTransition t4(&initial_state, &r_without_p, 1.0, EVENT_R);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&p_happened);
      this->addState(&r_after_p);
      this->addState(&r_without_p);
    }
};
#endif