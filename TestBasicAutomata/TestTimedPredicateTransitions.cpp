#include <map>
#include <AUnit.h>

#include <State.hpp>
#include <transitions/timed/TimedAnyRequiredEventsActiveTransition.hpp>
#include <transitions/timed/predicates/TimePredicateWrapper.hpp>

using namespace aunit;

class TestTimedPredicateTransitions : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEqual(float a, float b, float epsilon = 0.0001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestTimedPredicateTransitions, Test_R_two_seconds_before) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedAnyRequiredEventsActiveTransition outerTransition(&a, &b, 1.0, EVENT_P, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    
    //when
    bool result = outerTransition.evaluate(EVENT_P, 2000, &lastEvents);

    //then
    assertTrue(result);
}

testF(TestTimedPredicateTransitions, Test_R_twelve_seconds_before) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedAnyRequiredEventsActiveTransition outerTransition(&a, &b, 1.0, EVENT_P, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    
    //when
    bool result = outerTransition.evaluate(EVENT_P, 12000, &lastEvents);

    //then
    assertFalse(result);
}