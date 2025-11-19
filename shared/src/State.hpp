#ifndef state_hpp
#define state_hpp

#include "Arduino.h"
#include <List.hpp>
#include <stdio.h>
#include <string.h>

#include "Verdict.hpp"

using namespace std;

class ProbTransition;

class State
{
  public:
    State(String name, Verdict indicatedVerdict);
    ~State();

    String getName();
    Verdict getIndicatedVerdict();
    void addOutgoingTransition(ProbTransition* t);
    bool removeOutgoingTransition(ProbTransition* t);
    bool deleteOutgoingTransition(ProbTransition* t);
    void deleteAllOutgoingTransitions();

    List<ProbTransition*>& getOutgoingTransitions();

  private:
    String name;
    List<ProbTransition*> outgoingTransitions;
    Verdict indicatedVerdict;
};

#endif