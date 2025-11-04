#ifndef ABCSplitAutomaton_hpp
#define ABCSplitAutomaton_hpp

#include "../../State.hpp"
#include "../../ProbTransition.hpp"
#include "../../ProbStatemachine.hpp"
#include "../../Events.hpp"
#include "../../transitions/ExactEventsMatchTransition.hpp"

class ABCSplitAutomaton : public ProbStatemachine {
  public:
    ABCSplitAutomaton() : ProbStatemachine() {
      static State<ProbTransition> initial_state("A", Verdict::INCONCLUSIVE);
      static State<ProbTransition> state_one("B", Verdict::SATISFIED);
      static State<ProbTransition> state_two("C", Verdict::VIOLATED);

      static ExactEventsMatchTransition t1(&initial_state, &state_one, 0.5, EVENT_P);
      static ExactEventsMatchTransition t2(&initial_state, &state_two, 0.5, EVENT_P);

      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      this->addState(&state_one);
      this->addState(&state_two);
    }
};
#endif