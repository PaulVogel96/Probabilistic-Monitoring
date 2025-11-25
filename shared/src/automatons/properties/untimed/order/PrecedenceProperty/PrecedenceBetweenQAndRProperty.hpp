#ifndef PrecedenceBetweenQAndRProperty_hpp
#define PrecedenceBetweenQAndRProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../../transitions/AnyRequiredEventsActiveTransition.hpp"
#include "../../../../../transitions/MixedEventsConditionTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//"Between Q holds and R holds, if P holds then it must be that case that S holds before P"
class PrecedenceBetweenQAndRProperty : public ProbStatemachine {
  public:
    PrecedenceBetweenQAndRProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* q_happened = new State("Q happened", Verdict::VIOLATED);
      auto* not_p_nor_s = new State("Neither P nor S happened", Verdict::VIOLATED);
      auto* s_happened = new State("S happened", Verdict::SATISFIED);
      auto* p_before_s = new State("P happened before S", Verdict::INCONCLUSIVE);
      auto* error = new State("Error", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_happened, 1.0, EVENT_Q);
      auto* t2 = new AllRequiredEventsActiveTransition(q_happened, initial_state, 1.0, EVENT_R);
      auto* t3 = new MixedEventsConditionTransition(q_happened, s_happened, 1.0, EVENT_S, EVENT_R);
      auto* t4 = new AllRequiredEventsInactiveTransition(q_happened, not_p_nor_s, 1.0, EVENT_P | EVENT_R | EVENT_S);
      auto* t5 = new AllRequiredEventsActiveTransition(not_p_nor_s, p_before_s, 1.0, EVENT_P);
      auto* t6 = new MixedEventsConditionTransition(not_p_nor_s, s_happened, 1.0, EVENT_S, EVENT_P);
      auto* t7 = new MixedEventsConditionTransition(not_p_nor_s, initial_state, 1.0, EVENT_R, EVENT_P | EVENT_S);
      auto* t8 = new AllRequiredEventsActiveTransition(s_happened, initial_state, 1.0, EVENT_R);
      auto* t9 = new AnyRequiredEventsActiveTransition(p_before_s, error, 1.0, EVENT_R | EVENT_S);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(q_happened);
      this->addState(not_p_nor_s);
      this->addState(s_happened);
      this->addState(p_before_s);
      this->addState(error);
    }
};
#endif