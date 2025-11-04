#ifndef state_hpp
#define state_hpp

#include "Arduino.h"
#include <List.hpp>
#include <stdio.h>
#include <string.h>

#include "Verdict.hpp"

using namespace std;

template <class T> class State
{
  public:
    State(String name, Verdict indicatedVerdict);
    String getName();
    Verdict getIndicatedVerdict();
    void addOutgoingTransition(T* t);
    bool removeOutgoingTransition(T* t);
    bool deleteOutgoingTransition(T* t);

    List<T*>& getOutgoingTransitions();

  private:
    String name;
    List<T*> outgoingTransitions;
    Verdict indicatedVerdict;
};

#endif