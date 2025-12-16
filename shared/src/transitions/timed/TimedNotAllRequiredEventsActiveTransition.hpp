#ifndef TimedNotAllRequiredEventsActivetransition_hpp
#define TimedNotAllRequiredEventsActivetransition_hpp

#include "StandardCplusplus.h"
#include <map>

#include "../../ProbTransition.hpp" 
#include "predicates/TimePredicateWrapper.hpp"

class TimedNotAllRequiredEventsActiveTransition : public ProbTransition {
  public:
    bool (*predicate)(uint32_t now,
                      const std::map<uint8_t, uint32_t>* lastEvents,
                      const std::map<uint8_t, bool>* eventsSeen,
                      void* ctx);
    void* predicateCtx;

    TimedNotAllRequiredEventsActiveTransition(
        State* source,
        State* target,
        float probability,
        uint8_t mask,
        TimePredicateWrapper* wrapper
    )
    : ProbTransition(source, target, probability, mask),
      predicate(TimePredicateWrapper::call),
      predicateCtx(wrapper) {}

    bool evaluate(uint8_t symbol,
                  uint32_t now,
                  const std::map<uint8_t, uint32_t>* lastEvents,
                  const std::map<uint8_t, bool>* eventsSeen) const override
    {
      if (symbol & EVENTS_MISSING) {
        return false;
      }

      if ( (symbol & this->getMask()) == this->getMask() ) {
        return false;
      }

      return predicate(now, lastEvents, eventsSeen, predicateCtx);
    }
};
#endif