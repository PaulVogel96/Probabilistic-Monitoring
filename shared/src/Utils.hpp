#ifndef Utils
#define Utils

#include <map>

#include "Verdict.hpp"

//Use ArgMax-method to calculate if property violation happens
bool isVerdictViolated(std::map<Verdict, float> verdictProbs){
  return verdictProbs[Verdict::VIOLATED] >= verdictProbs[Verdict::SATISFIED] &&
    verdictProbs[Verdict::VIOLATED] >=  verdictProbs[Verdict::INCONCLUSIVE];
}

String verdictMapToString(std::map<Verdict, float> verdictProbs) {
  String s;
  s.reserve(48);  // prevent reallocations

  s += "{S: ";
  s += String(verdictProbs[Verdict::SATISFIED], 2);
  s += "; V: ";
  s += String(verdictProbs[Verdict::VIOLATED], 2);
  s += "; I: ";
  s += String(verdictProbs[Verdict::INCONCLUSIVE], 2);
  s += "}";

  return s;
}
#endif