#ifndef AllRequiredEventsActiveTransition_hpp
#define AllRequiredEventsActiveTransition_hpp

#include "StandardCplusplus.h"
#include <map>

#include "../../ProbTransition.hpp" 

class AllRequiredEventsActiveTransition : public ProbTransition {
    public:
        using ProbTransition::ProbTransition;

        bool evaluate(uint8_t symbol, uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents, const std::map<uint8_t, bool>* eventsSeen) const override {
            if (symbol & EVENTS_MISSING) {
                return (this->getMask() & EVENTS_MISSING) != 0;
            }
            return (symbol & this->getMask()) == this->getMask();
        }
};
#endif