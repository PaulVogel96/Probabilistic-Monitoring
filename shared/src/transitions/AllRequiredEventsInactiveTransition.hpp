#ifndef AllRequiredEventsInactiveTransition_hpp
#define AllRequiredEventsInactiveTransition_hpp

#include "../ProbTransition.hpp" 

class AllRequiredEventsInactiveTransition : public ProbTransition {
    public:
        using ProbTransition::ProbTransition;

        bool shouldFire(uint8_t symbol) const override {
            return (symbol & this->getMask()) == 0;
        }
};
#endif