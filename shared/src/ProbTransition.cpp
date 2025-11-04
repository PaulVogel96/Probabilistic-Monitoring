#include "ProbTransition.hpp"

ProbTransition::ProbTransition(State<ProbTransition>* source, State<ProbTransition>* target, float probability, uint8_t mask)
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

void ProbTransition::setSource(State<ProbTransition>* s)
{
    this->source = s;
    s->addOutgoingTransition(this);
};

State<ProbTransition>* ProbTransition::getSource()
{
    return this->source;
}

void ProbTransition::setTarget(State<ProbTransition>* s)
{
    this->target = s;
};

State<ProbTransition>* ProbTransition::getTarget()
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

uint8_t ProbTransition::getMask()
{
    return this->mask;
}
