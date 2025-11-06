#ifndef ExactEventsMatchTransition_hpp
#define ExactEventsMatchTransition_hpp

#include "../ProbTransition.hpp" 

class ExactEventsActiveTransition : public ProbTransition {
    public:
        using ProbTransition::ProbTransition;

        bool shouldFire(uint8_t symbol) const override {
            return (symbol == this->getMask());
        }
};
#endif