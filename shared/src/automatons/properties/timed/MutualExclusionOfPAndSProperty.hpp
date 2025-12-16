#ifndef MutualExclusionOfPAndSProperty_hpp
#define MutualExclusionOfPAndSProperty_hpp

#include "../../../State.hpp"
#include "../../../transitions/untimed/AllRequiredEventsActiveTransition.hpp"
#include "../../../transitions/untimed/ExactEventsInactiveTransition.hpp"
#include "../../../transitions/untimed/MixedEventsConditionTransition.hpp"
#include "../../../ProbStatemachine.hpp"

//"p may occur only when s is false (i.e., no p triggers inside any s-true window)"
class MutualExclusionOfPAndSProperty : public ProbStatemachine {
  public:
    MutualExclusionOfPAndSProperty() : ProbStatemachine() {
      auto* initial_state = new State("Initial State", Verdict::SATISFIED);
      auto* p_holds_while_s = new State("P happened while S holds", Verdict::VIOLATED);

      new AllRequiredEventsActiveTransition(initial_state, p_holds_while_s, 1.0, EVENT_P | EVENT_S);
      new MixedEventsConditionTransition(p_holds_while_s, initial_state, 1.0, EVENT_P, EVENT_S);
      new MixedEventsConditionTransition(p_holds_while_s, initial_state, 1.0, EVENT_S, EVENT_P);
      new ExactEventsInactiveTransition(p_holds_while_s, initial_state, 1.0, EVENT_P | EVENT_S);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(p_holds_while_s);
    }
};
#endif