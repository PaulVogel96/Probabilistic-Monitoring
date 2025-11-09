#ifndef UniversalityBetweenQAndRProperty_hpp
#define UniversalityBetweenQAndRProperty_hpp

#include "../../../../State.hpp"
#include "../../../../ProbTransition.hpp"
#include "../../../../transitions/AllRequiredEventsActiveTransition.hpp"
#include "../../../../transitions/AllRequiredEventsInactiveTransition.hpp"
#include "../../../../transitions/MixedEventsConditionTransition.hpp"
#include "../../../../ProbStatemachine.hpp"

//Between Q and R, it is always the case that P holds
class UniversalityBetweenQAndRProperty : public ProbStatemachine {
  public:
    UniversalityBetweenQAndRProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::SATISFIED);
      static State<ProbTransition> p_happened_after_q("P happened after Q", Verdict::SATISFIED);
      static State<ProbTransition> not_p_happened_after_q("Not P happened after Q", Verdict::SATISFIED);
      static State<ProbTransition> r_happened_after_q_and_not_p("R happened after Q and P", Verdict::VIOLATED);

      static AllRequiredEventsActiveTransition t1(&initial_state, &q_happened, 1.00, EVENT_Q);
      static AllRequiredEventsActiveTransition t2(&q_happened, &initial_state, 1.0, EVENT_R);
      static MixedEventConditionTransition t3(&q_happened, &p_happened_after_q, 1.0, EVENT_P, EVENT_R);
      static AllRequiredEventsInactiveTransition t4(&q_happened, &not_p_happened_after_q, 0.01, EVENT_P | EVENT_R);
      static AllRequiredEventsActiveTransition t5(&p_happened_after_q, &initial_state, 1.00, EVENT_R);
      static AllRequiredEventsInactiveTransition t6(&p_happened_after_q, &not_p_happened_after_q, 1.0, EVENT_P);
      static AllRequiredEventsActiveTransition t7(&not_p_happened_after_q, &r_happened_after_q_and_not_p, 1.00, EVENT_R);
      
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;
      this->addState(&q_happened);
      this->addState(&p_happened_after_q);
      this->addState(&not_p_happened_after_q);
      this->addState(&r_happened_after_q_and_not_p);
    }
};
#endif