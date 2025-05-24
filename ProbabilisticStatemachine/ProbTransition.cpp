#include "ProbTransition.hpp"

ProbTransition::ProbTransition(State<ProbTransition>* source, State<ProbTransition>* target, float probability, char triggger)
{
    this->source = source;
    this->source->addOutgoingTransition(this);
    this->target = target;
    this->probability = probability;
    this->trigger = trigger;
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

void ProbTransition::setSync(event e)
{
    this->sync = e;
};

event ProbTransition::getSync()
{
    return this->sync;
}

void ProbTransition::setProbability(float probability)
{
    this->probability = probability;
}

float ProbTransition::getProbability()
{
    return this->probability;
}

void ProbTransition::setTrigger(char c)
{
    this->trigger = c;
}

char ProbTransition::getTrigger()
{
    return this->trigger;
}
