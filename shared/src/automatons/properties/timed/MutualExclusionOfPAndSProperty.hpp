#ifndef MutualExclusionOfPAndSProperty_hpp
#define MutualExclusionOfPAndSProperty_hpp

#include "../../../State.hpp"
#include "../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/untimed/ExactEventsActiveTransition.hpp"
#include "../../../transitions/untimed/ExactEventsInactiveTransition.hpp"
#include "../../../ProbStatemachine.hpp"

//"p may occur only when s is false (i.e., no p triggers inside any s-true window)"
class MutualExclusionOfPAndSProperty : public ProbStatemachine {
  public:
    MutualExclusionOfPAndSProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* p_holds = new State("P happened while S holds", Verdict::VIOLATED);

      auto* p_and_s = new AllRequiredEventsActiveTransition(initial_state, p_holds, 1.0, EVENT_P | EVENT_S);
      auto* not_p_and_s1 = new ExactEventsActiveTransition(p_holds, initial_state, 1.0, EVENT_P);
      auto* not_p_and_s2 = new ExactEventsActiveTransition(p_holds, initial_state, 1.0, EVENT_S);
      auto* not_p_and_s3 = new ExactEventsInactiveTransition(p_holds, initial_state, 1.0, EVENT_P | EVENT_S);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_holds);
    }
};
#endif