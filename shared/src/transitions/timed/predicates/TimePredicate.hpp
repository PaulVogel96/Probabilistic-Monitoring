#ifndef TimePredicate_hpp
#define TimePredicate_hpp

#include <map>

#include "TimeComparator.hpp"
#include "Predicates.hpp"

struct TimePredicate {
    uint8_t eventType;
    TimeComparator comparator;
    uint32_t threshold;

    bool operator()(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents) const {
        return generic_time_predicate(now, lastEvents, eventType, comparator, threshold);
    }
};
#endif