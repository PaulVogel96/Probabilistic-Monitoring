#ifndef AnyRequiredEventInactiveTransition_hpp
#define AnyRequiredEventInactiveTransition_hpp

#include "../ProbTransition.hpp" 

class AnyRequiredEventsInactiveTransition : public ProbTransition {
    public:
        using ProbTransition::ProbTransition;

        bool shouldFire(uint8_t symbol) const override {
            return (symbol & this->getMask()) != this->getMask();
        }
};
#endif