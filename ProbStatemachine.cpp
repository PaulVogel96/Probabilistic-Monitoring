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

ProbStatemachine::~ProbStatemachine(){
    //  delete all states here?
};

State<ProbTransition>* ProbStatemachine::getInitialState()
{
    return this->initialState;
}

State<ProbTransition>* ProbStatemachine::addState(State<ProbTransition>* state)
{
    // we are adding pre-initialized States
    // State<ProbTransition>* state = new State<ProbTransition>(name);

    this->statePointers.add(state);
    this->states.insert(std::make_pair(state, 0));
    return state;
};

std::map<State<ProbTransition>*, float> ProbStatemachine::getCurrentStates()
{
    return this->states;
}

void ProbStatemachine::setReached(event i)
{
    std::map<State<ProbTransition>*, float>& oldStates = this->states;
    for (auto it = oldStates.begin(); it != oldStates.end(); ++it)
    {
        State<ProbTransition>* state = it->first;
        float prob = it->second;
        if (prob > 0)
        {
            bool enabled = false;
            List<ProbTransition*>& transitions = state->getOutgoingTransitions();
            for (int t = 0; t < transitions.getSize(); t++)
            {
                ProbTransition* transition = transitions[t];
                if (transition->isEnabled(i))
                {
                    this->states[transition->getTarget()] += (prob * transition->getProb());
                    enabled = true;
                }
            }
            if (enabled)
                this->states[state] -= prob;
        }
    }
};

// void ProbStatemachine::changeStates(char trigger){
//   std::map<State<ProbTransition>*, float>& oldStates = this->states;
//   for(auto it = oldStates.begin(); it != oldStates.end(); ++it){
//     Serial.println("debug changeState()");
//     State<ProbTransition>* state = it->first;
//     Serial.print(state->toString());
//     float prob = it -> second;
//     Serial.println(prob);
//     if(prob > 0){
//       bool enabled = false;
//       List<ProbTransition*>& transitions = state->getOutgoingTransitions();
//       for(int t = 0; t < transitions.getSize(); t++){
//         ProbTransition* transition = transitions[t];
//         if(transition->isTrigger(trigger)){
//           this->states[transition->getTarget()] += (prob * transition->getProb());
//           prob *= transition->getProb();
//           enabled = true;
//         }
//       }
//       if(enabled)
//         this->states[state] -= prob;
//     }
//   }
// }

void ProbStatemachine::changeStates(char trigger)
{
    // temporary map to store the new probabilities after transitions
    std::map<State<ProbTransition>*, float> newStates = this->states;
    // Iterate through the current states
    std::map<State<ProbTransition>*, float>& oldStates = this->states;
    for (auto it = oldStates.begin(); it != oldStates.end(); ++it)
    {
        State<ProbTransition>* state = it->first;
        float prob = it->second;

        if (prob > 0)
        {
            bool enabled = false;
            List<ProbTransition*>& transitions = state->getOutgoingTransitions();
            for (int t = 0; t < transitions.getSize(); t++)
            {
                ProbTransition* transition = transitions[t];
                if (transition->isTrigger(trigger))
                {
                    newStates[transition->getTarget()] += (prob * transition->getProb());
                    prob *= transition->getProb();
                    enabled = true;
                }
            }
            if (enabled)
                newStates[state] -= prob;
        }
    }
    this->states = newStates;
}

// gets most probable state
State<ProbTransition>* ProbStatemachine::getCurrentState()
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

State<ProbTransition>* ProbStatemachine::getState(String name)
{
    List<State<ProbTransition>*> states = this->statePointers;
    for (int i = 0; i < states.getSize(); i++)
    {
        if (states[i]->toString() == name)
        {
            return states[i];
        }
    }
    return NULL;
}

// state.prob soll auf 1, rest auf 0 gesetzt werden
void ProbStatemachine::reset(String state)
{
    std::map<State<ProbTransition>*, float>& oldStates = this->states;

    for (auto it = oldStates.begin(); it != oldStates.end(); ++it)
    {
        State<ProbTransition>* s = it->first;
        float prob = it->second;

        this->states[s] = (s->toString() == state);
    }
}

float ProbStatemachine::probToBeIn(String state)
{
    List<State<ProbTransition>*>& currStates = this->statePointers;
    for (int i = 0; i < currStates.getSize(); i++)
    {
        State<ProbTransition>* s = currStates[i];
        if (s->toString() == state)
            return this->states[s];
    }
    return 0;
}