#ifndef TimedMixedEventsConfitionTransition_hpp
#define TimedMixedEventsConfitionTransition_hpp

#include "StandardCplusplus.h"
#include <map>

#include "../../ProbTransition.hpp" 
#include "predicates/TimePredicateWrapper.hpp"

class TimedMixedEventsConditionTransition : public ProbTransition {
    public:
        bool (*predicate)(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents, const std::map<uint8_t, bool>* eventsSeen, void* ctx);
        void* predicateCtx;

        TimedMixedEventsConditionTransition(
            State* source, 
            State* target,
            float probability, 
            uint8_t activeMask,
            uint8_t inactiveMask,
            TimePredicateWrapper* wrapper
        )
        : ProbTransition(source, target, probability, 0),
        predicate(TimePredicateWrapper::call),
        predicateCtx(wrapper),
        activeMask(activeMask), 
        inactiveMask(inactiveMask)
        {
        }
        
        bool evaluate(uint8_t symbol, uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents, const std::map<uint8_t, bool>* eventsSeen) const override
        {
            if ((symbol & activeMask) != activeMask) {
                return false;
            }
            if ((symbol & inactiveMask) != 0) {
                return false;
            }
            return predicate(now, lastEvents, eventsSeen, predicateCtx);
        }

    private:
        uint8_t activeMask;
        uint8_t inactiveMask;
};
#endif