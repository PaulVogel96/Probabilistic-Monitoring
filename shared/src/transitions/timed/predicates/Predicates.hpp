#ifndef Predicates_hpp
#define Predcates_hpp

#include <map>

#include "TimeComparator.hpp"

bool generic_time_predicate(
  uint32_t now, 
  const std::map<uint8_t, uint32_t>* lastEvents, 
  const std::map<uint8_t, bool>* eventsSeen,
  uint8_t event_type, 
  TimeComparator comparator, 
  uint32_t firstThreshold, 
  uint32_t secondThreshold
);
#endif