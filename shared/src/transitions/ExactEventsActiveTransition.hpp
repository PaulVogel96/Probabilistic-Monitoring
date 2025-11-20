#ifndef ExactEventsMatchTransition_hpp
#define ExactEventsMatchTransition_hpp

#include "../ProbTransition.hpp" 

class ExactEventsActiveTransition : public ProbTransition {
    public:
        using ProbTransition::ProbTransition;

        bool evaluate(uint8_t symbol) const override {
            if (symbol & EVENTS_MISSING) {
                return (this->getMask() & EVENTS_MISSING) != 0;
            }
            return (symbol == this->getMask());
        }
};
#endif