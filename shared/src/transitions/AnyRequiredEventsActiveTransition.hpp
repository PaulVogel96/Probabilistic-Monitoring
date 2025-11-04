#ifndef AnyRequiredEventsActiveTransition_hpp
#define AnyRequiredEventsActiveTransition_hpp

#include "../ProbTransition.hpp" 

class AnyRequiredEventsActiveTransition : public ProbTransition {
    public:
        using ProbTransition::ProbTransition;

        bool shouldFire(uint8_t symbol) const override {
            return (symbol & this->getMask()) != 0;
        }
};

#endif /* AnyRequiredEventsActiveTransition_hpp*/