#include <map>

#include <./events.hpp>
#include "Predicates.hpp"
#include "TimeComparator.hpp"

bool generic_time_predicate(
    uint32_t now,
    const std::map<uint8_t, uint32_t>* lastEvents,
    const std::map<uint8_t, bool>* eventsSeen,
    uint8_t event_type,
    TimeComparator comparator,
    uint32_t firstThreshold,
    uint32_t secondThreshold
)
{
    auto it = lastEvents->find(event_type);
    auto itSeen = eventsSeen->find(event_type);
    bool seen = itSeen->second;
    if (it == lastEvents->end()) {
        return false;
    }

    uint32_t difference = now - it->second;

    switch (comparator) {
        case TimeComparator::LESS:          return seen ? difference <  firstThreshold : false;
        case TimeComparator::LESS_EQUAL:    return seen ? difference <= firstThreshold : false;
        case TimeComparator::GREATER:       return seen ? difference >  firstThreshold : now > firstThreshold;
        case TimeComparator::GREATER_EQUAL: return seen ? difference >= firstThreshold : now >= firstThreshold;
        case TimeComparator::EQUAL:         return seen ? difference == firstThreshold : false;
        case TimeComparator::BETWEEN:       return seen ? difference >= firstThreshold && difference <= secondThreshold : false;
        case TimeComparator::NOT_BETWEEN:   return seen ? !(difference >= firstThreshold && difference <= secondThreshold) : false;
    }
    return false;
}