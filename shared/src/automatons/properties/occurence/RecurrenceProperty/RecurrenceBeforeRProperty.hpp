#ifndef RecurrenceBeforeRProperty_hpp
#define RecurrenceBeforeRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"Before R holds, P holds repeatedly"
class RecurrenceBeforeRProperty : public ProbStatemachine {
  public:
    RecurrenceBeforeRProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::VIOLATED);
      static State<ProbTransition> p_holds("P happened", Verdict::SATISFIED);
      static State<ProbTransition> r_reached1("R reached", Verdict::VIOLATED);
      static State<ProbTransition> r_reached2("R reached", Verdict::SATISFIED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &p_holds, 1.0, EVENT_P);
      static AllRequiredEventsInactiveTransition t2(&p_holds, &initial_state, 1.0, EVENT_P);
      static AllRequiredEventsActiveTransition t3(&initial_state, &r_reached1, 1.0, EVENT_R);
      static AllRequiredEventsActiveTransition t4(&p_holds, &r_reached2, 1.0, EVENT_R);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&p_holds);
      this->addState(&r_reached1);
      this->addState(&r_reached2);
    }
};
#endif