#include "Results.hpp"

Results::Results(){
    // do nothing
}

Results::~Results(){
    // do nothing
}

std::map<State<ProbTransition>*, float> Results::getProbableStates(){
  return probableStates;
}

State<ProbTransition>* Results::addProbableState(State<ProbTransition>* state, float probability)
{
  this->probableStates[state] = probability;
  return state;
};

std::map<Verdict, float> Results::getVerdictProbabilities(){
  return std::map<Verdict, float>();
}