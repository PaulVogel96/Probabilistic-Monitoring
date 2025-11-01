#include "../../../../../State.hpp"
#include "../../../../../ProbTransition.hpp"
#include "../../../../../ProbStatemachine.hpp"

class ResponseAfterQProperty : public ProbStatemachine {
  public:
    ResponseAfterQProperty() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
      static State<ProbTransition> q_happened("Q happened", Verdict::SATISFIED);
      static State<ProbTransition> p_happened("P happened", Verdict::INCONCLUSIVE);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&initial_state, &q_happened, 1.0, 'Q');
      static ProbTransition t2(&q_happened, &p_happened, 0.99, 'P');
      static ProbTransition t3(&q_happened, &q_happened, 0.01, 'P');
      static ProbTransition t4(&p_happened, &q_happened, 1.0, 'S');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&initial_state);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&q_happened);
      this->addState(&p_happened);
    }
};