#ifndef UntilBetweenQAndRProperty_hpp
#define UntilBetweenQAndRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../transitions/ExactEventsInactiveTransition.hpp"
#include "../../../../transitions/ExactEventsActiveTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//"After Q holds, P holds without interruption until S holds before R holds"
class UntilBetweenQAndRProperty : public ProbStatemachine {
  public:
    UntilBetweenQAndRProperty() : ProbStatemachine() {
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_holds("Q holds", Verdict::INCONCLUSIVE);
      static State<ProbTransition> p_holds("P holds", Verdict::INCONCLUSIVE);
      static State<ProbTransition> not_p_holds_before_p("P holds", Verdict::INCONCLUSIVE);
      static State<ProbTransition> not_p_holds_after_p("P holds", Verdict::VIOLATED);
      static State<ProbTransition> s_holds("S holds", Verdict::INCONCLUSIVE);
      static State<ProbTransition> r_holds("R holds (but PS did not)", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_holds, 1.0, EVENT_Q);
      static AllRequiredEventsActiveTransition t2(&q_holds, &initial_state, 1.0, EVENT_R);
      static AllRequiredEventsActiveTransition t3(&q_holds, &p_holds, 1.0, EVENT_P);
      static AllRequiredEventsInactiveTransition t4(&q_holds, &not_p_holds_before_p, 1.0, EVENT_P | EVENT_R);
      static AllRequiredEventsActiveTransition t5(&not_p_holds_before_p, &p_holds, 1.0, EVENT_P);
      static ExactEventsInactiveTransition t6(&p_holds, &not_p_holds_after_p, 1.0, EVENT_P);
      static ExactEventsActiveTransition t7(&p_holds, &s_holds, 1.0, EVENT_S);
      static ExactEventsActiveTransition t8(&p_holds, &not_p_holds_after_p, 1.0, EVENT_R);
      static ExactEventsActiveTransition t9(&s_holds, &initial_state, 1.0, EVENT_R);
      
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&q_holds);
      this->addState(&p_holds);
      this->addState(&not_p_holds_after_p);
      this->addState(&not_p_holds_before_p);
      this->addState(&s_holds);
      this->addState(&r_holds);
    }
};
#endif