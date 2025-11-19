#ifndef ExactEventsDoesNotMatchTransition_hpp
#define ExactEventsDoesNotMatchTransition_hpp

#include "../ProbTransition.hpp" 

class ExactEventsInactiveTransition : public ProbTransition {
    public:
        using ProbTransition::ProbTransition;

        bool shouldFire(uint8_t symbol) const override {
            uint8_t missing = getMask() & static_cast<uint8_t>(~symbol);
            return missing == getMask();
        }
};
#endif