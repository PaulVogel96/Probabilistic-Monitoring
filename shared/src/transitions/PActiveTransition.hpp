#ifndef PActiveTransition_hpp
#define PActiveTransition_hpp

#include "../ProbTransition.hpp" 
#include "../events.hpp"

class PActiveTransition : public ProbTransition {
    public:
        PActiveTransition(State<ProbTransition>* source, State<ProbTransition>* target, float probability)
            : ProbTransition(source, target, probability, EVENT_P){}

        bool shouldFire(uint8_t symbol) const override {
            return allRequiredEventsActive(symbol, this->getMask());
        }
};

#endif /* PActiveTransition*/