#ifndef TimedAllRequiredEventsActiveTransition_hpp
#define TimedAllRequiredEventsActiveTransition_hpp

#include "StandardCplusplus.h"
#include <map>

#include "../../ProbTransition.hpp" 

class TimedAllRequiredEventsActiveTransition : public ProbTransition {
    public:
        bool (*predicate)(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents);

        TimedAllRequiredEventsActiveTransition(
            State* source, 
            State* target,
            float probability, 
            uint8_t mask,
            bool (*predicate)(uint32_t, const std::map<uint8_t, uint32_t>* lastEvents)
        )
        : ProbTransition(source, target, probability, mask),
        predicate(predicate)
        {

        }
        
        bool evaluate(uint8_t symbol, uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents) const override
        {
            bool eventInactive;
            if (symbol & EVENTS_MISSING) {
                eventInactive = (this->getMask() & EVENTS_MISSING) != 0;
            } else {
                eventInactive = (symbol & this->getMask()) == this->getMask();
            }
            if (!eventInactive){
                return false;
            }
            return predicate(now, lastEvents);
        }
};
#endif