#ifndef ProbStatemachine_hpp
#define ProbStatemachine_hpp
#include "List.hpp"
#include "ProbTransition.hpp"
#include "StandardCplusplus.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// compiles with  Arduino AVR Boards version 1.8.2

using namespace std;

class ProbStatemachine
{
  public:
    ProbStatemachine(State<ProbTransition>* initialState);
    State<ProbTransition>* getInitialState();
    ~ProbStatemachine();
    void removeState(String name);
    void setReached(event i);
    State<ProbTransition>* addState(State<ProbTransition>* name);
    std::map<State<ProbTransition>*, float> getCurrentStates();
    State<ProbTransition>* getCurrentState();
    void changeStates(char trigger);
    State<ProbTransition>* getState(String name);
    void reset(String state);
    float probToBeIn(String state);

  private:
    bool switchState();
    std::map<State<ProbTransition>*, float> states;
    State<ProbTransition>* initialState;
    List<State<ProbTransition>*> statePointers;
};

#endif /* ProbStatemachine_hpp */