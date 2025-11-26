#ifndef TimedMixedEventsConfitionTransition_hpp
#define TimedMixedEventsConfitionTransition_hpp

#include "StandardCplusplus.h"
#include <map>

#include "../../ProbTransition.hpp" 

class TimedMixedEventsConfitionTransition : public ProbTransition {
    public:
        bool (*predicate)(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents);

        TimedMixedEventsConfitionTransition(
            State* source, 
            State* target,
            float probability,
            uint8_t activeMask,
            uint8_t inactiveMask,
            bool (*predicate)(uint32_t, const std::map<uint8_t, uint32_t>* lastEvents)
        )
        : ProbTransition(source, target, probability, 0),
        predicate(predicate),
        activeMask(activeMask), 
        inactiveMask(inactiveMask)
        {

        }
        
        bool evaluate(uint8_t symbol, uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents) const override
        {
            bool eventInactive;
            if (symbol & EVENTS_MISSING) {
                eventInactive = (this->getMask() & EVENTS_MISSING) != 0;
            } else {
                eventInactive = (symbol & this->getMask()) == 0;
            }
            if (!eventInactive){
                return false;
            }

            return predicate(now, lastEvents);
        }

    private:
        uint8_t activeMask;
        uint8_t inactiveMask;
};
#endif