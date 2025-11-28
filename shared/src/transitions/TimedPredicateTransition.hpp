#ifndef TimedTransition_hpp
#define TimedTransition_hpp

#include "StandardCplusplus.h"
#include <map>

#include "../ProbTransition.hpp" 

class TimedPredicateAllRequiredEventsInactiveTransition : public ProbTransition {
    public:
        bool (*predicate)(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents);

        TimedPredicateAllRequiredEventsInactiveTransition(
            State* source, 
            State* target,
            float probability, 
            uint8_t mask,
            ProbTransition* innerTransition, 
            bool (*predicate)(uint32_t, const std::map<uint8_t, uint32_t>* lastEvents
        ))
        : ProbTransition(source, target, probability, mask),
        predicate(predicate)
        {}
        
        bool evaluate(uint8_t symbol, uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents) const override
        {
            if(!innerTransition->evaluate(symbol, now, lastEvents)){
                return false;
            }
            return predicate(now, lastEvents);
        }
};
#endif