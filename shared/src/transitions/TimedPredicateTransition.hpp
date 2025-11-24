#ifndef TimedTransition_hpp
#define TimedTransition_hpp

#include "StandardCplusplus.h"
#include <map>

#include "../ProbTransition.hpp" 

class TimedPredicateTransition : public ProbTransition {
    public:
        ProbTransition* innerTransition;
        bool (*predicate)(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents);

        TimedPredicateTransition(ProbTransition* innerTransition, bool (*predicate)(uint32_t, const std::map<uint8_t, uint32_t>* lastEvents))
            : ProbTransition(innerTransition->getSource(), innerTransition->getTarget(), innerTransition->getProbability(), innerTransition->getMask()),
            innerTransition(innerTransition),
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