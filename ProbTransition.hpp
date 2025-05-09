#ifndef ProbTransition_hpp
#define ProbTransition_hpp

#include "State.hpp"
#include <stdio.h>

class ProbTransition
{
  public:
    ProbTransition(State<ProbTransition>* source, State<ProbTransition>* target);
    ProbTransition(State<ProbTransition>* source, State<ProbTransition>* target, float probability);
    ~ProbTransition();
    State<ProbTransition>* getSource();
    State<ProbTransition>* getTarget();
    void setSource(State<ProbTransition>* s);
    void setTarget(State<ProbTransition>* s);
    void setSync(event e);
    bool isEnabled(event e);
    void setProbability(float prob);
    float getProb();
    void setTrigger(char c);
    bool isTrigger(char c);
    char getTrigger();

  private:
    State<ProbTransition>* source;
    State<ProbTransition>* target;
    event sync;
    float probability;
    char trigger;
};

#endif /* ProbTransition_*/