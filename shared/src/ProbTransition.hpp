#ifndef ProbTransition_hpp
#define ProbTransition_hpp

#include "StandardCplusplus.h"
#include <stdio.h>
#include <map>

#include "events.hpp"

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

    virtual bool evaluate(uint8_t symbol, uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents, const std::map<uint8_t, bool>* eventsSeen) const = 0;

  private:
    State* source;
    State* target;
    float probability;
    uint8_t mask;
};

#endif