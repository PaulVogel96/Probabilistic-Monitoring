#include "../State.hpp"
#include "../ProbTransition.hpp"
#include "../ProbStatemachine.hpp"

class DoubleSplitAutomatonWithLoop : public ProbStatemachine {
  public:
    //               |--- D
    // ___   |--- B -|
    // |  |  |       |--- E
    // A --- |       
    //       |
    //       |       |--- F
    //       |--- C -|
    //               |--- G
    DoubleSplitAutomatonWithLoop() : ProbStatemachine() {
      //static declaration of states
      static State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
      static State<ProbTransition> b("B", Verdict::INCONCLUSIVE);
      static State<ProbTransition> c("C", Verdict::INCONCLUSIVE);
      static State<ProbTransition> d("D", Verdict::SATISFIED);
      static State<ProbTransition> e("E", Verdict::VIOLATED);
      static State<ProbTransition> f("F", Verdict::SATISFIED);
      static State<ProbTransition> g("G", Verdict::VIOLATED);

      //static declaration of transitions
      //transitions are registered automatically in the constructor
      static ProbTransition t1(&a, &b, 0.3, 'a');
      static ProbTransition t2(&a, &c, 0.5, 'a');
      static ProbTransition t3(&a, &a, 0.2, 'a');
      static ProbTransition t4(&b, &d, 0.4, 'b');
      static ProbTransition t5(&b, &e, 0.6, 'b');
      static ProbTransition t6(&c, &f, 0.8, 'c');
      static ProbTransition t7(&c, &g, 0.2, 'c');

      //register states and transitions in automaton

      //initial state
      this->initialState = this->addState(&a);
      this->states[this->initialState] = 1;

      //register other states
      this->addState(&b);
      this->addState(&c);
      this->addState(&d);
      this->addState(&e);
      this->addState(&f);
      this->addState(&g);

    }
};