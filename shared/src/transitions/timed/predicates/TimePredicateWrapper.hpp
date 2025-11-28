#ifndef TimePredicateWrapper_hpp
#define TimePredicateWrapper_hpp

#include "TimePredicate.hpp"

struct TimePredicateWrapper {
    TimePredicate pred;

    static bool call(uint32_t now,
                     const std::map<uint8_t, uint32_t>* lastEvents,
                     void* ctx)
    {
        return static_cast<TimePredicateWrapper*>(ctx)->pred(now, lastEvents);
    }
};
#endif