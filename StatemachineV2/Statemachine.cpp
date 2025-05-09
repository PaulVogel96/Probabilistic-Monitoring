#include "Statemachine.hpp"
#include "List.hpp"
#include "State.hpp"
#include "Transition.hpp"
#include "WString.h"

// changed it so that States arent created here but you have to define them first to build a
// Statemachine with them...
Statemachine::Statemachine(State<Transition>* initialState)
{
    this->currentState = this->addState(initialState);
};

Statemachine::~Statemachine(){};

State<Transition>* Statemachine::addState(State<Transition>* state)
{
    this->states.add(state);
    return state;
};

State<Transition>* Statemachine::getCurrentState()
{
    return this->currentState;
}

// using this function to see in which State I land with event e
void Statemachine::setReached(event e)
{
    List<Transition*> outgoingTransitions = this->currentState->getOutgoingTransitions();
    int numTransitions = outgoingTransitions.getSize();
    for (int i = 0; i < numTransitions; i++)
    {
        Transition* t = outgoingTransitions[i];
        if (t->isEnabled(e))
        {
            this->currentState = t->getTarget();
            return;
        }
    }
};

void Statemachine::changeCurrentState(char trigger)
{
    Serial.print("Current State in function: ");    // debug
    Serial.println(this->currentState->toString()); // debug

    List<Transition*> outgoingTransitions = this->getCurrentState()->getOutgoingTransitions();
    int numTransitions = outgoingTransitions.getSize();

    for (int i = 0; i < numTransitions; i++)
    {
        Transition* t = outgoingTransitions[i];
        State<Transition>* Source = t->getSource();
        State<Transition>* Target = t->getTarget();
        if (t->isTrigger(trigger))
        {
            Serial.println("...transitioning...");
            this->currentState = t->getTarget();
            return;
        }
        else
        {
            Serial.println("...no possible transition...");
        }
    }
};

State<Transition>* Statemachine::getState(String name)
{
    List<State<Transition>*> allstates = this->states;
    int numStates = allstates.getSize();
    for (int i = 0; i < numStates; i++)
    {
        State<Transition>* state = allstates[i];
        if (state->toString() == name)
        {
            return state;
        }
    }
    return NULL;
}

void Statemachine::reset(String toState)
{
    if (this->getState(toState) != NULL)
    {
        this->currentState = this->getState(toState);
    }
}