#ifndef Results_hpp
#define Results_hpp

#include <map>
#include "State.hpp"
#include "ProbTransition.hpp"
#include "Verdict.hpp"

class Results
{
  public:
    Results();
    ~Results();

    std::map<String, float> getStateProbabilities();
    State<ProbTransition>* addProbableState(State<ProbTransition>* name, float probability);

    std::map<Verdict, float> getVerdictProbabilities();

  private:
    std::map<State<ProbTransition>*, float> probableStates;  
};
#endif /* Results_hpp */