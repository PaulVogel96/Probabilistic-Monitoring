#ifndef state_hpp
#define state_hpp

#include "Arduino.h"
#include <List.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
// sind das die Events für die Transitionen? wieso werden die hier definiert?
enum event
{
    Q,
    R,
    P,
    S,
    left,
    right,
    up,
    down
};

template <class T> class State
{
  public:
    State(String name);
    String toString();
    void addOutgoingTransition(T* t);
    bool removeOutgoingTransition(T* t);
    bool deleteOutgoingTransition(T* t);

    List<T*> getOutgoingTransitions();

  private:
    String name;
    List<T*> outgoingTransitions;
};

#endif /* state_hpp */