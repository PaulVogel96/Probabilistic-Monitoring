#ifndef UntilProperty_hpp
#define UntilProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"P holds until S holds"
class UntilProperty : public ProbStatemachine {
  public:
    UntilProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::INCONCLUSIVE);
      static State<ProbTransition> s_holds("S", Verdict::SATISFIED);
      static State<ProbTransition> not_p_or_s_holds("NOT_P", Verdict::VIOLATED);

      static AllRequiredEventsInactiveTransition t1(&initial_state, &not_p_or_s_holds, 1.0, EVENT_P | EVENT_S);
      static AllRequiredEventsActiveTransition t2(&initial_state, &s_holds, 1.0, EVENT_S);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&s_holds);
      this->addState(&not_p_or_s_holds);
    }
};
#endif