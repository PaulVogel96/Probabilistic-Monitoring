#ifndef Utils
#define Utils

#include <map>

#include "Verdict.hpp"

//Use ArgMax-method to calculate if property violation happens
bool isVerdictViolated(std::map<Verdict, float> verdictProbs){
  return verdictProbs[Verdict::VIOLATED] >= verdictProbs[Verdict::SATISFIED] &&
    verdictProbs[Verdict::VIOLATED] >=  verdictProbs[Verdict::INCONCLUSIVE];
}
#endif