#include <map>
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

void ProbStatemachine::changeStates(uint8_t trigger)
{
    std::map<State<ProbTransition>*, float> newStates = this->states;
    std::map<State<ProbTransition>*, float>& oldStates = this->states;
    for (auto it = oldStates.begin(); it != oldStates.end(); ++it)
    {
        State<ProbTransition>* state = it->first;
        float prob = it->second;
        float restprob = it->second;
        if (prob > 0)
        {
            bool enabled = false;
            List<ProbTransition*>& transitions = state->getOutgoingTransitions();
            for (int t = 0; t < transitions.getSize(); t++)
            {
                ProbTransition* transition = transitions[t];
                if (transition->shouldFire(trigger) && transition->getTarget() != state)
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
}

void ProbStatemachine::processEvents(const std::vector<uint8_t>& events) {
    for (auto symbol : events) {
        changeStates(symbol);
    }
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