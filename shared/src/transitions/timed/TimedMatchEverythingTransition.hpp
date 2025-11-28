#ifndef TimedMatchEverythingTransition_hpp
#define TimedMatchEverythingTransition_hpp

#include "StandardCplusplus.h"
#include <map>

#include "../../ProbTransition.hpp" 

class TimedMatchEverythingTransition : public ProbTransition {
    public:
        bool (*predicate)(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents);

        TimedMatchEverythingTransition(
            State* source, 
            State* target,
            float probability,
            bool (*predicate)(uint32_t, const std::map<uint8_t, uint32_t>* lastEvents)
        )
        : ProbTransition(source, target, probability, 0),
        predicate(predicate)
        {

        }
        
        bool evaluate(uint8_t symbol, uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents) const override
        {
            return predicate(now, lastEvents);
        }
};
#endif