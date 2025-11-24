#ifndef AnyRequiredEventsActiveTransition_hpp
#define AnyRequiredEventsActiveTransition_hpp

#include "StandardCplusplus.h"
#include <map>

#include "../ProbTransition.hpp" 

class AnyRequiredEventsActiveTransition : public ProbTransition {
    public:
        using ProbTransition::ProbTransition;

        bool evaluate(uint8_t symbol, uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents) const override {
            if (symbol & EVENTS_MISSING) {
                return (this->getMask() & EVENTS_MISSING) != 0;
            }
            return (symbol & this->getMask()) != 0;
        }
};
#endif