#include <map>
#include "ProbStatemachine.hpp"
#include "List.hpp"
#include "ProbTransition.hpp"
#include "State.hpp"
#include "WString.h"

ProbStatemachine::ProbStatemachine(State* initialState)
{
    this->initialState = this->addState(initialState);
    this->states[this->initialState] = 1;
};

ProbStatemachine::ProbStatemachine(){
};

ProbStatemachine::~ProbStatemachine(){
    for (auto& entry : states) {
        State* s = entry.first;
        s->deleteAllOutgoingTransitions();
    }

    for (auto& entry : states) {
        delete entry.first;
    }
    states.clear();
};

State* ProbStatemachine::getInitialState()
{
    return this->initialState;
}

State* ProbStatemachine::addState(State* state)
{
    this->statePointers.add(state);
    this->states.insert(std::make_pair(state, 0));
    return state;
};

void ProbStatemachine::removeState(State* state){
    List<State*> states = this->statePointers;
    for (int i = 0; i < states.getSize(); i++)
    {
        if (states[i]->getName() == state->getName())
        {
            statePointers.remove(i);
        }
    }

    this->states.erase(state);
}

State* ProbStatemachine::getState(String name)
{
    for (int i = 0; i < this->statePointers.getSize(); i++)
    {
        if (this->statePointers[i]->getName() == name)
        {
            return this->statePointers[i];
        }
    }
    return NULL;
}

std::map<State*, float> ProbStatemachine::getCurrentStates()
{
    return this->states;
}


void ProbStatemachine::reset(String state)
{
    std::map<State*, float>& oldStates = this->states;

    for (auto it = oldStates.begin(); it != oldStates.end(); ++it)
    {
        State* s = it->first;
        float prob = it->second;

        this->states[s] = (s->getName() == state);
    }
}

void ProbStatemachine::changeStates(uint8_t trigger, uint32_t timestamp)
{
    std::map<State*, float> newStates = this->states;
    std::map<State*, float>& oldStates = this->states;
    for (auto it = oldStates.begin(); it != oldStates.end(); ++it)
    {
        State* state = it->first;
        float prob = it->second;
        float restprob = it->second;
        if (prob > 0)
        {
            bool enabled = false;
            List<ProbTransition*>& transitions = state->getOutgoingTransitions();
            for (int t = 0; t < transitions.getSize(); t++)
            {
                ProbTransition* transition = transitions[t];
                if (transition->evaluate(trigger, timestamp, &this->lastEventOcurrences) && transition->getTarget() != state)
                {
                    newStates[transition->getTarget()] += (prob * transition->getProbability());
                    restprob -= (prob * transition->getProbability());
                    enabled = true;
                }
            }
            if (enabled){
                newStates[state] = restprob;
            }
        }
    }
    this->states = newStates;
    this->setOccurenceOfAt(trigger, timestamp);
}

void ProbStatemachine::processEvents(const std::vector<uint8_t>& events, const std::vector<uint32_t>& timestamps) {
    //expect events to be the same size as timestamps
    for(int i = 0; i < events.size(); i++){
        changeStates(events[i], timestamps[i]);
    }
}

void ProbStatemachine::setOccurenceOfAt(uint8_t events, uint32_t timestamp){
    if((events & EVENT_P) != 0){
        lastEventOcurrences[EVENT_P] = timestamp;
    }
    if((events & EVENT_Q) != 0){
        lastEventOcurrences[EVENT_Q] = timestamp;
    }
    if((events & EVENT_R) != 0){
        lastEventOcurrences[EVENT_R] = timestamp;
    }
    if((events & EVENT_S) != 0){
        lastEventOcurrences[EVENT_S] = timestamp;
    }
    if((events & EVENT_N) != 0){
        lastEventOcurrences[EVENT_N] = timestamp;
    }
    if((events & EVENT_X) != 0){
        lastEventOcurrences[EVENT_X] = timestamp;
    }
    if((events & EVENT_Y) != 0){
        lastEventOcurrences[EVENT_Y] = timestamp;
    }
}

uint32_t ProbStatemachine::getLastOccurenceOf(uint8_t event){
    return lastEventOcurrences[event];
}

State* ProbStatemachine::getMostLikelyCurrentState()
{
    State* s = this->initialState;
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
    List<State*>& currStates = this->statePointers;
    for (int i = 0; i < currStates.getSize(); i++)
    {
        State* s = currStates[i];
        if (s->getName() == state)
            return this->states[s];
    }
    return 0;
}

std::map<String, float> ProbStatemachine::getStateProbabilities(){
    std::map<String, float> results;
    for (auto it = this->states.begin(); it != this->states.end(); ++it)
    {
        if(it->second > 0){
        results[it->first->getName()] = it->second;
        }
    }
    return results;
}

std::map<Verdict, float> ProbStatemachine::getVerdictProbabilities() {
    std::map<Verdict, float> results;
    results[Verdict::INCONCLUSIVE] = 0.0;
    results[Verdict::SATISFIED] = 0.0;
    results[Verdict::VIOLATED] = 0.0;
    for (auto it = this->states.begin(); it != this->states.end(); ++it)
    {
        if(it->second > 0){
            results[it->first->getIndicatedVerdict()] += it->second;
        }
    }
    return results;
}