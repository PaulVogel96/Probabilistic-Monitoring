#ifndef ProbTransition_hpp
#define ProbTransition_hpp

#include "events.hpp"
#include <stdio.h>

class State;

class ProbTransition
{
  public:
    ProbTransition(State* source, State* target, float probability, uint8_t mask);
    ~ProbTransition();

    void setSource(State* s);
    State* getSource();

    void setTarget(State* s);
    State* getTarget();

    void setProbability(float probability);
    float getProbability();

    void setMask(uint8_t c);
    uint8_t getMask() const;

    virtual bool evaluate(uint8_t symbol) const = 0;

  private:
    State* source;
    State* target;
    float probability;
    uint8_t mask;
};

#endif