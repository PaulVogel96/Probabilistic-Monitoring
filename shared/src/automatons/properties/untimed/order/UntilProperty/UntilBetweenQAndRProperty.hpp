#ifndef UntilBetweenQAndRProperty_hpp
#define UntilBetweenQAndRProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../transitions/untimed/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../../transitions/untimed/MixedEventsConditionTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"After Q holds, P holds without interruption until S holds before R holds"
class UntilBetweenQAndRProperty : public ProbStatemachine {
  public:
    UntilBetweenQAndRProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* q_holds = new State("Q holds", Verdict::INCONCLUSIVE);
      auto* p_holds = new State("P holds", Verdict::INCONCLUSIVE);
      auto* not_p_holds_before_p = new State("P holds", Verdict::INCONCLUSIVE);
      auto* not_p_holds_after_p = new State("P holds", Verdict::VIOLATED);
      auto* s_holds = new State("S holds", Verdict::INCONCLUSIVE);
      auto* r_holds = new State("R holds (but PS did not)", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_holds, 1.0, EVENT_Q);
      auto* t2 = new AllRequiredEventsActiveTransition(q_holds, initial_state, 1.0, EVENT_R);
      auto* t3 = new AllRequiredEventsActiveTransition(q_holds, p_holds, 1.0, EVENT_P);
      auto* t4 = new AllRequiredEventsInactiveTransition(q_holds, not_p_holds_before_p, 1.0, EVENT_P | EVENT_R);
      auto* t5 = new AllRequiredEventsActiveTransition(not_p_holds_before_p, p_holds, 1.0, EVENT_P);
      auto* t6 = new AllRequiredEventsActiveTransition(p_holds, s_holds, 1.0, EVENT_S);
      auto* t7 = new AllRequiredEventsActiveTransition(p_holds, initial_state, 1.0, EVENT_R);
      auto* t8 = new AllRequiredEventsInactiveTransition(p_holds, not_p_holds_after_p, 1.0, EVENT_P | EVENT_S | EVENT_R);
      auto* t9 = new AllRequiredEventsActiveTransition(s_holds, initial_state, 1.0, EVENT_R);
      
      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(q_holds);
      this->addState(p_holds);
      this->addState(not_p_holds_after_p);
      this->addState(not_p_holds_before_p);
      this->addState(s_holds);
      this->addState(r_holds);
    }
};
#endif