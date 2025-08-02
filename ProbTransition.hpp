#ifndef ProbTransition_hpp
#define ProbTransition_hpp

#include "State.hpp"
#include "event.hpp"
#include <stdio.h>

class ProbTransition
{
  public:
    ProbTransition(State<ProbTransition>* source, State<ProbTransition>* target, float probability, char trigger);
    ~ProbTransition();

    void setSource(State<ProbTransition>* s);
    State<ProbTransition>* getSource();

    void setTarget(State<ProbTransition>* s);
    State<ProbTransition>* getTarget();

    void setSync(event e);
    event getSync();

    void setProbability(float probability);
    float getProbability();

    void setTrigger(char c);
    char getTrigger();

  private:
    State<ProbTransition>* source;
    State<ProbTransition>* target;
    event sync;
    float probability;
    char trigger;
};

#endif /* ProbTransition_*/