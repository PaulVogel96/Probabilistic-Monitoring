#include "ProbStatemachine.hpp"
#include "List.hpp"
#include "ProbTransition.hpp"
#include "State.hpp"
#include "WString.h"

ProbStatemachine::ProbStatemachine(State<ProbTransition>* initialState)
{
    this->initialState = this->addState(initialState);
    this->states[this->initialState] = 1;
};

ProbStatemachine::ProbStatemachine(){
    // do nothing
};

ProbStatemachine::~ProbStatemachine(){
    // delete all states here?
};

State<ProbTransition>* ProbStatemachine::getInitialState()
{
    return this->initialState;
}

State<ProbTransition>* ProbStatemachine::addState(State<ProbTransition>* state)
{
    this->statePointers.add(state);
    this->states.insert(std::make_pair(state, 0));
    return state;
};

void ProbStatemachine::removeState(State<ProbTransition>* state){
    List<State<ProbTransition>*> states = this->statePointers;
    for (int i = 0; i < states.getSize(); i++)
    {
        if (states[i]->getName() == state->getName())
        {
            statePointers.remove(i);
        }
    }

    this->states.erase(state);
}

State<ProbTransition>* ProbStatemachine::getState(String name)
{
    List<State<ProbTransition>*> states = this->statePointers;
    for (int i = 0; i < states.getSize(); i++)
    {
        if (states[i]->getName() == name)
        {
            return states[i];
        }
    }
    return NULL;
}

std::map<State<ProbTransition>*, float> ProbStatemachine::getCurrentStates()
{
    return this->states;
}


void ProbStatemachine::reset(String state)
{
    std::map<State<ProbTransition>*, float>& oldStates = this->states;

    for (auto it = oldStates.begin(); it != oldStates.end(); ++it)
    {
        State<ProbTransition>* s = it->first;
        float prob = it->second;

        this->states[s] = (s->getName() == state);
    }
}

void ProbStatemachine::changeStates(char trigger)
{
    // temporary map to store the new probabilities after transitions
    std::map<State<ProbTransition>*, float> newStates = this->states;
    // Iterate through the current states
    // Serial.print("Input: ");
    // Serial.println(trigger);
    // Serial.println("Calculating State change, iterating over old state-probability map");
    std::map<State<ProbTransition>*, float>& oldStates = this->states;
    for (auto it = oldStates.begin(); it != oldStates.end(); ++it)
    {
        State<ProbTransition>* state = it->first;
        float prob = it->second;
        float restprob = it->second;
        Serial.print("found state: ");
        Serial.print(state->getName() + ", ");
        Serial.println(prob);
        if (prob > 0)
        {
            Serial.println("probability > 0");
            bool enabled = false;
            List<ProbTransition*> transitions = state->getOutgoingTransitions();
            Serial.print("found ");
            Serial.print(transitions.getSize());
            Serial.println(" transitions");
            for (int t = 0; t < transitions.getSize(); t++)
            {
                ProbTransition* transition = transitions[t];
                Serial.print("Found Transition with trigger: ");
                Serial.print(transition->getTrigger());
                Serial.print(" and destination: ");
                Serial.println(transition->getTarget()->getName());
                if (transition->getTrigger() == trigger && transition->getTarget() != state)
                {
                    Serial.println("Transition triggered");
                    Serial.print("Followup State probability: ");
                    Serial.println(prob * transition->getProbability());
                    newStates[transition->getTarget()] += (prob * transition->getProbability());
                    restprob -= (prob * transition->getProbability());
                    enabled = true;
                }
            }
            if (enabled)
                Serial.print("Restprobability ");
                Serial.println(restprob);
                newStates[state] = restprob;
        }
    }
    this->states = newStates;
}

State<ProbTransition>* ProbStatemachine::getMostLikelyCurrentState()
{
    State<ProbTransition>* s = this->initialState;
    float p = 0;
    for (auto it = this->states.begin(); it != this->states.end(); ++it)
    {
        auto const& state = it->first;
        auto const& prob = it->second;
        if (prob > p)
        {
            s = state;
            p = prob;
        }
    }
    return s;
}

float ProbStatemachine::probToBeIn(String state)
{
    List<State<ProbTransition>*>& currStates = this->statePointers;
    for (int i = 0; i < currStates.getSize(); i++)
    {
        State<ProbTransition>* s = currStates[i];
        if (s->getName() == state)
            return this->states[s];
    }
    return 0;
}

Results ProbStatemachine::getResults(){
    Results results;

    for(auto it = states.begin(); it != states.end(); ++it){
        State<ProbTransition>* state = it ->first;
        float prob = it->second;
        if(prob > 0){
            results.addProbableState(state, prob);
        }
    }

    return results;
}