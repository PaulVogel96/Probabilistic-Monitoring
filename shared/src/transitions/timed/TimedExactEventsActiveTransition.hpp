#ifndef TimedExactEventsActiveTransition_hpp
#define TimedExactEventsActiveTransition_hpp

#include "StandardCplusplus.h"
#include <map>

#include "../../ProbTransition.hpp" 
#include "predicates/TimePredicateWrapper.hpp"

class TimedExactEventsActiveTransition : public ProbTransition {
    public:
        bool (*predicate)(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents, const std::map<uint8_t, bool>* eventsSeen, void* ctx);
        void* predicateCtx;

        TimedExactEventsActiveTransition(
            State* source, 
            State* target,
            float probability, 
            uint8_t mask,
            TimePredicateWrapper* wrapper
        )
        : ProbTransition(source, target, probability, mask),
        predicate(TimePredicateWrapper::call),
        predicateCtx(wrapper)
        {

        }
        
        bool evaluate(uint8_t symbol, uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents, const std::map<uint8_t, bool>* eventsSeen) const override
        {
            bool eventInactive;
            if (symbol & EVENTS_MISSING) {
                eventInactive = (this->getMask() & EVENTS_MISSING) != 0;
            } else {
                eventInactive = (symbol == this->getMask());
            }
            if (!eventInactive){
                return false;
            }

            return predicate(now, lastEvents, eventsSeen, predicateCtx);
        }
};
#endif