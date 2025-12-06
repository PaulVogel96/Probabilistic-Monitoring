#include <map>
#include <AUnit.h>

#include <State.hpp>
#include <transitions/timed/TimedAllRequiredEventsActiveTransition.hpp>
#include <transitions/timed/TimedAllRequiredEventsInactiveTransition.hpp>
#include <transitions/timed/TimedAnyRequiredEventsActiveTransition.hpp>
#include <transitions/timed/TimedAnyRequiredEventsInactiveTransition.hpp>
#include <transitions/timed/TimedExactEventsActiveTransition.hpp>
#include <transitions/timed/TimedExactEventsInactiveTransition.hpp>
#include <transitions/timed/TimedMatchEverythingTransition.hpp>
#include <transitions/timed/TimedMixedEventsConditionTransition.hpp>
#include <transitions/timed/predicates/TimePredicateWrapper.hpp>

using namespace aunit;

class TestTimedPredicateTransitions : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEqual(float a, float b, float epsilon = 0.0001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestTimedPredicateTransitions, AllRequiredEventsActive_fires_when_event_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedAllRequiredEventsActiveTransition transition(&a, &b, 1.0, EVENT_P, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P, 2000, &lastEvents, &eventSeen);

    //then
    assertTrue(result);
}

testF(TestTimedPredicateTransitions, AllRequiredEventsActive_does_not_fire_when_event_incorrect_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedAllRequiredEventsActiveTransition transition(&a, &b, 1.0, EVENT_P, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_X, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, AllRequiredEventsActive_does_not_fire_when_event_correct_and_predicate_incorrect) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 1000}};
    TimedAllRequiredEventsActiveTransition transition(&a, &b, 1.0, EVENT_P, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, AllRequiredEventsInactive_fires_when_event_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedAllRequiredEventsInactiveTransition transition(&a, &b, 1.0, EVENT_P | EVENT_Q, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_X, 2000, &lastEvents, &eventSeen);

    //then
    assertTrue(result);
}

testF(TestTimedPredicateTransitions, AllRequiredEventsInactive_does_not_fire_when_event_incorrect_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedAllRequiredEventsInactiveTransition transition(&a, &b, 1.0, EVENT_P, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, AllRequiredEventsInactive_does_not_fire_when_event_correct_and_predicate_incorrect) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 1000}};
    TimedAllRequiredEventsInactiveTransition transition(&a, &b, 1.0, EVENT_P | EVENT_Q, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, AnyRequiredEventsActive_fires_when_event_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedAnyRequiredEventsActiveTransition transition(&a, &b, 1.0, EVENT_P | EVENT_Q, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_Q, 2000, &lastEvents, &eventSeen);

    //then
    assertTrue(result);
}

testF(TestTimedPredicateTransitions, AnyRequiredEventsActive_does_not_fire_when_event_incorrect_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedAnyRequiredEventsActiveTransition transition(&a, &b, 1.0, EVENT_P | EVENT_S, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_X, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, AnyRequiredEventsActive_does_not_fire_when_event_correct_and_predicate_incorrect) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 1000}};
    TimedAnyRequiredEventsActiveTransition transition(&a, &b, 1.0, EVENT_P | EVENT_N, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, AnyRequiredEventsInactive_fires_when_event_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedAnyRequiredEventsInactiveTransition transition(&a, &b, 1.0, EVENT_P | EVENT_Q, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_Q, 2000, &lastEvents, &eventSeen);

    //then
    assertTrue(result);
}

testF(TestTimedPredicateTransitions, AnyRequiredEventsInactive_does_not_fire_when_event_incorrect_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedAnyRequiredEventsInactiveTransition transition(&a, &b, 1.0, EVENT_P | EVENT_S, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P | EVENT_S, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, AnyRequiredEventsInactive_does_not_fire_when_event_correct_and_predicate_incorrect) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 1000}};
    TimedAnyRequiredEventsInactiveTransition transition(&a, &b, 1.0, EVENT_P | EVENT_N, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, ExactRequiredEventsActive_fires_when_event_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedExactEventsActiveTransition transition(&a, &b, 1.0, EVENT_P, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P, 2000, &lastEvents, &eventSeen);

    //then
    assertTrue(result);
}

testF(TestTimedPredicateTransitions, ExactRequiredEventsActive_does_not_fire_when_event_incorrect_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedExactEventsActiveTransition transition(&a, &b, 1.0, EVENT_P | EVENT_S, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, ExactEventsActive_does_not_fire_when_event_correct_and_predicate_incorrect) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 1000}};
    TimedExactEventsActiveTransition transition(&a, &b, 1.0, EVENT_P | EVENT_N, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P | EVENT_N, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, ExactRequiredEventsInactive_fires_when_event_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedExactEventsInactiveTransition transition(&a, &b, 1.0, EVENT_P, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_X, 2000, &lastEvents, &eventSeen);

    //then
    assertTrue(result);
}

testF(TestTimedPredicateTransitions, ExactRequiredEventsInactive_does_not_fire_when_event_incorrect_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedExactEventsInactiveTransition transition(&a, &b, 1.0, EVENT_P | EVENT_S, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P | EVENT_Q, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, ExactEventsInactive_does_not_fire_when_event_correct_and_predicate_incorrect) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 1000}};
    TimedExactEventsInactiveTransition transition(&a, &b, 1.0, EVENT_P | EVENT_N, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_X, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, MatchEverything_fires_when_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedMatchEverythingTransition transition(&a, &b, 1.0, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    

    //when
    bool result = transition.evaluate(EVENT_NONE, 2000, &lastEvents, &eventSeen);

    //then
    assertTrue(result);
}

testF(TestTimedPredicateTransitions, MatchEverything_does_not_fire_when_predicate_incorrect) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 1000}};
    TimedMatchEverythingTransition transition(&a, &b, 1.0, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_NONE, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, MixedEventsCondition_fires_when_event_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedMixedEventsConditionTransition transition(&a, &b, 1.0, EVENT_P, EVENT_R, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P, 2000, &lastEvents, &eventSeen);

    //then
    assertTrue(result);
}

testF(TestTimedPredicateTransitions, MixedEventsCondition_does_not_fire_when_event_incorrect_and_predicate_correct) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
    TimedMixedEventsConditionTransition transition(&a, &b, 1.0, EVENT_P, EVENT_S, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P | EVENT_S, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}

testF(TestTimedPredicateTransitions, MixedEventsCondition_does_not_fire_when_event_correct_and_predicate_incorrect) {
    //given
    State a("A", Verdict::INCONCLUSIVE);
    State b("B", Verdict::SATISFIED);
    TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 1000}};
    TimedMixedEventsConditionTransition transition(&a, &b, 1.0, EVENT_P, EVENT_N, pred);
    std::map<uint8_t, uint32_t> lastEvents;
    lastEvents[EVENT_R] = 0;
    std::map<uint8_t, bool> eventSeen;
    eventSeen[EVENT_R] = true;
    
    //when
    bool result = transition.evaluate(EVENT_P, 2000, &lastEvents, &eventSeen);

    //then
    assertFalse(result);
}