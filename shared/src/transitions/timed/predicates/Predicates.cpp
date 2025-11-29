#include <map>

#include <./events.hpp>
#include "Predicates.hpp"
#include "TimeComparator.hpp"

bool generic_time_predicate(
    uint32_t now,
    const std::map<uint8_t, uint32_t>* lastEvents,
    uint8_t event_type,
    TimeComparator comparator,
    uint32_t firstThreshold,
    uint32_t secondThreshold
)
{
    auto it = lastEvents->find(event_type);
    if (it == lastEvents->end()) {
        return false;
    }

    uint32_t difference = now - it->second;

    switch (comparator) {
        case TimeComparator::LESS:          return difference <  firstThreshold;
        case TimeComparator::LESS_EQUAL:    return difference <= firstThreshold;
        case TimeComparator::GREATER:       return difference >  firstThreshold;
        case TimeComparator::GREATER_EQUAL: return difference >= firstThreshold;
        case TimeComparator::EQUAL:         return difference == firstThreshold;
        case TimeComparator::BETWEEN:       return difference >= firstThreshold && difference <= secondThreshold;
        case TimeComparator::NOT_BETWEEN:   return !(difference >= firstThreshold && difference <= secondThreshold);
    }
    return false;
}