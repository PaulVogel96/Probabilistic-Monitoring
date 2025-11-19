#ifndef ProbStatemachine_hpp
#define ProbStatemachine_hpp

#include "Arduino.h"
#include "List.hpp"
#include "ProbTransition.hpp"
#include "Verdict.hpp"
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
    ProbStatemachine(State* initialState);
    ProbStatemachine();

    ~ProbStatemachine();

    State* getInitialState();

    State* addState(State* name);
    State* getState(String name);
    void removeState(State* state);
    std::map<State*, float> getCurrentStates();
    std::map<String, float> getStateProbabilities();
    std::map<Verdict, float> getVerdictProbabilities();

    void reset(String state);
    void changeStates(uint8_t trigger);
    void processEvents(const vector<uint8_t>& events);
    
    State* getMostLikelyCurrentState();
    float probToBeIn(String state);

  protected:
    std::map<State*, float> states;
    State* initialState;

  private:
    bool switchState();
    List<State*> statePointers;
};

#endif /* ProbStatemachine_hpp */