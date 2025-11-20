#ifndef ExactEventsDoesNotMatchTransition_hpp
#define ExactEventsDoesNotMatchTransition_hpp

#include "../ProbTransition.hpp" 

class ExactEventsInactiveTransition : public ProbTransition {
    public:
        using ProbTransition::ProbTransition;

        bool evaluate(uint8_t symbol) const override {
            if (symbol & EVENTS_MISSING) {
                return (this->getMask() & EVENTS_MISSING) != 0;
            }
            uint8_t missing = getMask() & static_cast<uint8_t>(~symbol);
            return missing == getMask();
        }
};
#endif