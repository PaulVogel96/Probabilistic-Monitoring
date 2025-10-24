// #include "../../State.hpp"
// #include "../../ProbTransition.hpp"
// #include "../../ProbStatemachine.hpp"

// /*
// How does this differ from AbsenceBetweenQAndRProperty?
// */
// class AbsenceAfterQUntilRProperty : public ProbStatemachine {
//   public:
//     AbsenceAfterQUntilRProperty() : ProbStatemachine() {
//       //static declaration of states
//       static State<ProbTransition> initial_state("Initial State", Verdict::SATISFIED);
//       static State<ProbTransition> q_happened("Q happened", Verdict::SATISFIED);
//       static State<ProbTransition> p_happened_after_q("P happened after Q", Verdict::SATISFIED);
//       static State<ProbTransition> r_happened_after_q_and_p("R happened after Q and P", Verdict::VIOLATED);

//       //static declaration of transitions
//       //transitions are registered automatically in the constructor
//       static ProbTransition t1(&initial_state, &initial_state, 0.99, 'X');
//       static ProbTransition t1(&initial_state, &q_happened, 0.01, 'X'); //0.01 chance that X is actually Q
//       static ProbTransition t1(&initial_state, &q_happened, 1.00, 'Q');

//       static ProbTransition t1(&q_happened, &q_happened, 0.99, 'X');
//       static ProbTransition t1(&q_happened, &p_happened_after_q, 0.01, 'X'); //0.01 chance that X is actually P
//       static ProbTransition t1(&q_happened, &p_happened_after_q, 1.00, 'P'); //0.01 chance that X is actually Q

//       static ProbTransition t1(&p_happened_after_q, &p_happened_after_q, 0.99, 'X');
//       static ProbTransition t1(&p_happened_after_q, &r_happened_after_q_and_p, 0.01, 'X'); //0.01 chance that X is actually R
//       static ProbTransition t1(&p_happened_after_q, &r_happened_after_q_and_p, 1.00, 'R'); //0.01 chance that X is actually Q
      
//       //initial state
//       this->initialState = this->addState(&initial_state);
//       this->states[this->initialState] = 1;

//       //register other states
//       this->addState(&b);
//     }
// };