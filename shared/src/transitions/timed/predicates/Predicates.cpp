#include <map>

#include <./events.hpp>
#include "Predicates.hpp"
#include "TimeComparator.hpp"

bool generic_time_predicate(
    uint32_t now,
    const std::map<uint8_t, uint32_t>* lastEvents,
    uint8_t event_type,
    TimeComparator comparator,
    uint32_t thresholdMs)
{
    auto it = lastEvents->find(event_type);
    if (it == lastEvents->end()) {
        return false;
    }

    uint32_t difference = now - it->second;

    switch (comparator) {
        case TimeComparator::LESS:          return difference <  thresholdMs;
        case TimeComparator::LESS_EQUAL:    return difference <= thresholdMs;
        case TimeComparator::GREATER:       return difference >  thresholdMs;
        case TimeComparator::GREATER_EQUAL: return difference >= thresholdMs;
        case TimeComparator::EQUAL:         return difference == thresholdMs;
    }
    return false;
}