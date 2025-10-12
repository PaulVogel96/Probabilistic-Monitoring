#include "State.hpp"
#include "ProbTransition.hpp"
#include "ProbStatemachine.hpp"

class ABCSplitAutomaton : public ProbStatemachine {
  public:
    ABCSplitAutomaton() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
      static State<ProbTransition> b("B", Verdict::SATISFIED);
      static State<ProbTransition> c("C", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&a, &b, 0.5, 'a');
      static ProbTransition t2(&a, &c, 0.5, 'a');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&a);
      this->states[this->initialState] = 1;


      //register other states
      this->addState(&b);
      this->addState(&c);
    }
};