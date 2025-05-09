#ifndef Statemachine_hpp
#define Statemachine_hpp

#include "List.hpp"
#include "Transition.hpp"
#include <stdio.h>

using namespace std;

class Statemachine
{
  public:
    Statemachine(State<Transition>* initialState);
    ~Statemachine();
    //    unsigned int getClock();
    void reset(String toState);
    void removeState(String name);
    void setReached(event e); // as far as i understand, setReached changes the currents state
    void changeCurrentState(char trigger); // own function
    State<Transition>* addState(State<Transition>* state);
    State<Transition>* getCurrentState();
    State<Transition>* getState(String name);
    // Transition* addTransition(State<Transition>* source, State<Transition>* target);

  private:
    bool switchState();
    List<State<Transition>*> states;
    State<Transition>* currentState;
    //    unsigned int nextTimeGuard;
    //    unsigned long clock;
    //    unsigned long deltaFromMillis;
};

#endif /* Statemachine_hpp */