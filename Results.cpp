#include "Results.hpp"

Results::Results(){
    // do nothing
}

Results::~Results(){
    // do nothing
}

std::map<String, float> Results::getStateProbabilities(){
  std::map<String, float> results;
  for (auto it = this->probableStates.begin(); it != this->probableStates.end(); ++it)
  {
      results[it->first->getName()] = it->second;
  }
  return results;
}

State<ProbTransition>* Results::addProbableState(State<ProbTransition>* state, float probability)
{
  this->probableStates[state] = probability;
  return state;
};

std::map<Verdict, float> Results::getVerdictProbabilities(){
  return std::map<Verdict, float>();
}