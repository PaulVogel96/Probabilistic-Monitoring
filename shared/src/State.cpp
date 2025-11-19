#include "State.hpp"
#include "ProbTransition.hpp"

State::State(String name, Verdict indicatedVerdict)
{
    this->name = name;
    this->indicatedVerdict = indicatedVerdict;
}

State::~State(){
};

String State::getName()
{
    return this->name;
}

Verdict State::getIndicatedVerdict()
{
    return this->indicatedVerdict;
}

void State::addOutgoingTransition(ProbTransition* t)
{
    this->outgoingTransitions.add(t);
};


List<ProbTransition*>& State::getOutgoingTransitions()
{
    return this->outgoingTransitions;
};

bool State::removeOutgoingTransition(ProbTransition* t)
{
    int numTransitions = this->outgoingTransitions.getSize();
    for (int i = 0; i < numTransitions; i++)
    {
        ProbTransition* tr = outgoingTransitions[i];
        if (tr == t)
        {
            this->outgoingTransitions.remove(i);
            return true;
        }
    }
    return false;
};

void State::deleteAllOutgoingTransitions() {
    for (int i = 0; i < outgoingTransitions.getSize(); i++){
        delete outgoingTransitions[i];
    }
    outgoingTransitions.clear();
}