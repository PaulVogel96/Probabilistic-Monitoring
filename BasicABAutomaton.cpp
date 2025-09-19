#include "State.hpp"
#include "ProbTransition.hpp"
#include "ProbStatemachine.hpp"

class BasicABAutomaton : public ProbStatemachine {
  public:
    BasicABAutomaton() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> a("A");
      static State<ProbTransition> b("B");

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t(&a, &b, 1.0, 'a');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&a);
      this->states[this->initialState] = 1;


      //register other states
      this->addState(&b);

    }
};