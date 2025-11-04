#ifndef ExactEventsMatchTransition_hpp
#define ExactEventsMatchTransition_hpp

#include "../ProbTransition.hpp" 

class ExactEventsMatchTransition : public ProbTransition {
    public:
        using ProbTransition::ProbTransition;

        bool shouldFire(uint8_t symbol) const override {
            return (symbol == this->getMask());
        }
};

#endif /* ExactEventsMatchTransition_hpp*/