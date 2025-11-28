#ifndef Predicates_hpp
#define Predcates_hpp

#include <map>

bool generic_time_predicate(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents, uint8_t event_type, TimeComparator comparator, uint32_t thresholdMs);
#endif