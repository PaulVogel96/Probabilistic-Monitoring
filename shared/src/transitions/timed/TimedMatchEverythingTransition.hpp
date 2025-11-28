#ifndef TimedMatchEverythingTransition_hpp
#define TimedMatchEverythingTransition_hpp

#include "StandardCplusplus.h"
#include <map>

#include "../../ProbTransition.hpp" 
#include "predicates/TimePredicateWrapper.hpp"

class TimedMatchEverythingTransition : public ProbTransition {
    public:
        bool (*predicate)(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents, void* ctx);
        void* predicateCtx;

        TimedMatchEverythingTransition(
            State* source, 
            State* target,
            float probability,
            TimePredicateWrapper* wrapper
        )
        : ProbTransition(source, target, probability, 0),
        predicate(TimePredicateWrapper::call),
        predicateCtx(wrapper)
        {

        }
        
        bool evaluate(uint8_t symbol, uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents) const override
        {
            return predicate(now, lastEvents, predicateCtx);
        }
};
#endif