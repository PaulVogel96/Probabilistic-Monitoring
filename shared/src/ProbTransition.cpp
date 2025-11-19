#include "ProbTransition.hpp"
#include "State.hpp"

ProbTransition::ProbTransition(State* source, State* target, float probability, uint8_t mask)
{
    this->source = source;
    this->source->addOutgoingTransition(this);
    this->target = target;
    this->probability = probability;
    this->mask = mask;
}

ProbTransition::~ProbTransition()
{
}

void ProbTransition::setSource(State* s)
{
    this->source = s;
    s->addOutgoingTransition(this);
};

State* ProbTransition::getSource()
{
    return this->source;
}

void ProbTransition::setTarget(State* s)
{
    this->target = s;
};

State* ProbTransition::getTarget()
{
    return this->target;
};

void ProbTransition::setProbability(float probability)
{
    this->probability = probability;
}

float ProbTransition::getProbability()
{
    return this->probability;
}

void ProbTransition::setMask(uint8_t c)
{
    this->mask = c;
}

uint8_t ProbTransition::getMask() const
{
    return this->mask;
}
