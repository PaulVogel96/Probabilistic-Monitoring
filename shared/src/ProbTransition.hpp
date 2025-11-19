#ifndef ProbTransition_hpp
#define ProbTransition_hpp

#include "State.hpp"
#include "events.hpp"
#include <stdio.h>

class ProbTransition
{
  public:
    ProbTransition(State<ProbTransition>* source, State<ProbTransition>* target, float probability, uint8_t mask);
    ~ProbTransition();

    void setSource(State<ProbTransition>* s);
    State<ProbTransition>* getSource();

    void setTarget(State<ProbTransition>* s);
    State<ProbTransition>* getTarget();

    void setProbability(float probability);
    float getProbability();

    void setMask(uint8_t c);
    uint8_t getMask() const;

    virtual bool shouldFire(uint8_t symbol) const = 0;

  private:
    State<ProbTransition>* source;
    State<ProbTransition>* target;
    float probability;
    uint8_t mask;
};

#endif