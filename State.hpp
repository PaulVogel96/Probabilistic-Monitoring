#include <Vector.h>

#include <List.hpp>

#ifndef state_hpp
#define state_hpp

#include "Arduino.h"
#include <List.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;

template <class T> class State
{
  public:
    State(String name);
    String getName();
    void addOutgoingTransition(T* t);
    bool removeOutgoingTransition(T* t);
    bool deleteOutgoingTransition(T* t);

    List<T*> getOutgoingTransitions();

  private:
    String name;
    List<T*> outgoingTransitions;
};

#endif /* state_hpp */