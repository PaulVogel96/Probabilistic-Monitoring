#ifndef UniversalityBetweenQAndRProperty_hpp
#define UniversalityBetweenQAndRProperty_hpp

#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../../transitions/MixedEventsConditionTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

//Between Q and R, it is always the case that P holds
class UniversalityBetweenQAndRProperty : public ProbStatemachine {
  public:
    UniversalityBetweenQAndRProperty() : ProbStatemachine() {
      //static declaration of states
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* q_happened = new State("Q happened", Verdict::SATISFIED);
      auto* p_happened_after_q = new State("P happened after Q", Verdict::SATISFIED);
      auto* not_p_happened_after_q = new State("Not P happened after Q", Verdict::SATISFIED);
      auto* r_happened_after_q_and_not_p = new State("R happened after Q and P", Verdict::VIOLATED);

      auto* t1 = new AllRequiredEventsActiveTransition(initial_state, q_happened, 1.0, EVENT_Q);
      auto* t2 = new AllRequiredEventsActiveTransition(q_happened, initial_state, 1.0, EVENT_R);
      auto* t3 = new MixedEventsConditionTransition(q_happened, p_happened_after_q, 1.0, EVENT_P, EVENT_R);
      auto* t4 = new AllRequiredEventsInactiveTransition(q_happened, not_p_happened_after_q, 1.0, EVENT_P | EVENT_R);
      auto* t5 = new AllRequiredEventsActiveTransition(p_happened_after_q, initial_state, 1.0, EVENT_R);
      auto* t6 = new AllRequiredEventsInactiveTransition(p_happened_after_q, not_p_happened_after_q, 1.0, EVENT_P | EVENT_R);
      auto* t7 = new AllRequiredEventsActiveTransition(not_p_happened_after_q, r_happened_after_q_and_not_p, 1.0, EVENT_R);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(q_happened);
      this->addState(p_happened_after_q);
      this->addState(not_p_happened_after_q);
      this->addState(r_happened_after_q_and_not_p);
    }
};
#endif