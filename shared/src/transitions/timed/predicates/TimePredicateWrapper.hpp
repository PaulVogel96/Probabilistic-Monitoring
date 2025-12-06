#ifndef TimePredicateWrapper_hpp
#define TimePredicateWrapper_hpp

#include "TimePredicate.hpp"

struct TimePredicateWrapper {
    TimePredicate predicate;

    TimePredicateWrapper(const TimePredicate& pred)
        : predicate(pred) {}

    static bool call(
      uint32_t now,
      const std::map<uint8_t, uint32_t>* lastEvents, 
      const std::map<uint8_t, bool>* eventsSeen,
      void* ctx)
    {
        return static_cast<TimePredicateWrapper*>(ctx)->predicate(now, lastEvents, eventsSeen);
    }
};
#endif