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
    void changeStates(uint8_t trigger, uint32_t timestamp);
    void processEvents(const vector<uint8_t>& events, const vector<uint32_t>& timestamps);
    void setOccurenceOfAt(uint8_t events, uint32_t timestamp);
    uint32_t getLastOccurenceOf(uint8_t events);
    
    State* getMostLikelyCurrentState();
    float probToBeIn(String state);

  protected:
    std::map<State*, float> states;
    State* initialState;
    std::map<uint8_t, uint32_t> lastEventOcurrences;

  private:
    List<State*> statePointers;
};

#endif /* ProbStatemachine_hpp */