#ifndef AllRequiredEventsActiveTransition_hpp
#define AllRequiredEventsActiveTransition_hpp

#include "../ProbTransition.hpp" 

class AllRequiredEventsActiveTransition : public ProbTransition {
    public:
        using ProbTransition::ProbTransition;

        bool shouldFire(uint8_t symbol) const override {
            return (symbol & this->getMask()) == this->getMask();
        }
};
#endif