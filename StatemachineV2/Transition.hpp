//#include "WString.h"
#ifndef Transition_hpp
#define Transition_hpp

#include <stdio.h>
#include "State.hpp"

class Transition{
public:
    Transition(State<Transition>* source, State<Transition>* target);
    ~Transition();
    State<Transition>* getSource();
    State<Transition>* getTarget();
    // void setSource(State<Transition>* s);
    // void setTarget(State<Transition>* s);
    void setSync(event e);
    bool isEnabled(event e);
    void setTrigger(char trigger);
    bool isTrigger(char e);
    char getTrigger();
    
private:
    const State<Transition>* const source;
    const State<Transition>* const target;
    event sync;
    char trigger;
};

#endif /* Transition_hpp */