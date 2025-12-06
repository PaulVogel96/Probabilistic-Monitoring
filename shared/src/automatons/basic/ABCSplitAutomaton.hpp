#ifndef ABCSplitAutomaton_hpp
#define ABCSplitAutomaton_hpp

#include "../../State.hpp"
#include "../../ProbTransition.hpp"
#include "../../ProbStatemachine.hpp"
#include "../../Events.hpp"
#include "../../transitions/untimed/ExactEventsActiveTransition.hpp"

class ABCSplitAutomaton : public ProbStatemachine {
  public:
    ABCSplitAutomaton() : ProbStatemachine() {
      auto* initial_state = new State("A", Verdict::INCONCLUSIVE);
      auto* state_one = new State("B", Verdict::SATISFIED);
      auto* state_two = new State("C", Verdict::VIOLATED);

      auto* t1 = new ExactEventsActiveTransition(initial_state, state_one, 0.5, EVENT_P);
      auto* t2 = new ExactEventsActiveTransition(initial_state, state_two, 0.5, EVENT_P);

      this->initialState = this->addState(initial_state);
      this->states[this->initialState] = 1;
      this->addState(state_one);
      this->addState(state_two);
    }
};
#endif