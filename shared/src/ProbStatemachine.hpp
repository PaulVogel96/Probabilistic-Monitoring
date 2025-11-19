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
    ProbStatemachine();

    ~ProbStatemachine();

    State<ProbTransition>* getInitialState();

    State<ProbTransition>* addState(State<ProbTransition>* name);
    State<ProbTransition>* getState(String name);
    void removeState(State<ProbTransition>* state);
    std::map<State<ProbTransition>*, float> getCurrentStates();
    std::map<String, float> getStateProbabilities();
    std::map<Verdict, float> getVerdictProbabilities();

    void reset(String state);
    void changeStates(uint8_t trigger);
    void processEvents(const vector<uint8_t>& events);
    
    State<ProbTransition>* getMostLikelyCurrentState();
    float probToBeIn(String state);

  protected:
    std::map<State<ProbTransition>*, float> states;
    State<ProbTransition>* initialState;

  private:
    bool switchState();
    List<State<ProbTransition>*> statePointers;
};

#endif /* ProbStatemachine_hpp */