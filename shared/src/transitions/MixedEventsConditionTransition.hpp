#ifndef MixedEventsConditionTransition_hpp
#define MixedEventsConditionTransition_hpp

#include "../ProbTransition.hpp" 

class MixedEventsConditionTransition : public ProbTransition {
    public:
        MixedEventsConditionTransition(State* source,
                                  State* target,
                                  float probability,
                                  uint8_t activeMask,
                                  uint8_t inactiveMask)
        : ProbTransition(source, target, probability, 0),
          activeMask(activeMask), 
          inactiveMask(inactiveMask) {}

        bool evaluate(uint8_t symbol) const override {
            if (symbol & EVENTS_MISSING) {
                return (this->getMask() & EVENTS_MISSING) != 0;
            }
            bool allActive = (symbol & activeMask) == activeMask;
            bool allInactive = (symbol & inactiveMask) == 0;
            return allActive && allInactive;
        }

    private:
        uint8_t activeMask;
        uint8_t inactiveMask;
};
#endif