#include <AUnit.h>

#include <State.hpp>
#include <events.hpp>
#include <transitions/timed/predicates/TimePredicateWrapper.hpp>

using namespace aunit;

class TestTimePredicates : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEqual(float a, float b, float epsilon = 0.0001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestTimePredicates, predicate_less_than_true) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(9999, &lastEventOccurences, &eventSeen, pred);

  //then
  assertTrue(result);
}

testF(TestTimePredicates, predicate_less_than_false) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(10000, &lastEventOccurences, &eventSeen, pred);

  //then
  assertFalse(result);
}

testF(TestTimePredicates, predicate_less_equal_true_less) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS_EQUAL, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(9999, &lastEventOccurences, &eventSeen, pred);

  //then
  assertTrue(result);
}

testF(TestTimePredicates, predicate_less_equal_true_equal) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS_EQUAL, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(10000, &lastEventOccurences, &eventSeen, pred);

  //then
  assertTrue(result);
}

testF(TestTimePredicates, predicate_less_equal_false) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::LESS_EQUAL, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(10001, &lastEventOccurences, &eventSeen, pred);

  //then
  assertFalse(result);
}

testF(TestTimePredicates, predicate_equal_too_low) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::EQUAL, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(9999, &lastEventOccurences, &eventSeen, pred);

  //then
  assertFalse(result);
}

testF(TestTimePredicates, predicate_equal_true) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::EQUAL, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(10000, &lastEventOccurences, &eventSeen, pred);

  //then
  assertTrue(result);
}

testF(TestTimePredicates, predicate_equal_too_high) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::EQUAL, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(10001, &lastEventOccurences, &eventSeen, pred);

  //then
  assertFalse(result);
}

testF(TestTimePredicates, predicate_greater_equal_false) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::GREATER_EQUAL, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(9999, &lastEventOccurences, &eventSeen, pred);

  //then
  assertFalse(result);
}

testF(TestTimePredicates, predicate_greater_equal_true_equal) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::GREATER_EQUAL, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(10000, &lastEventOccurences, &eventSeen, pred);

  //then
  assertTrue(result);
}

testF(TestTimePredicates, predicate_greater_equal_true_greater) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::GREATER_EQUAL, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(10001, &lastEventOccurences, &eventSeen, pred);

  //then
  assertTrue(result);
}

testF(TestTimePredicates, predicate_greater_false_lower) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::GREATER, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(9999, &lastEventOccurences, &eventSeen, pred);

  //then
  assertFalse(result);
}

testF(TestTimePredicates, predicate_greater_false_equal) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::GREATER, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(10000, &lastEventOccurences, &eventSeen, pred);

  //then
  assertFalse(result);
}

testF(TestTimePredicates, predicate_greater_true) {
  //given
  TimePredicateWrapper* pred = new TimePredicateWrapper{TimePredicate{EVENT_R, TimeComparator::GREATER, 10000}};
  std::map<uint8_t, uint32_t> lastEventOccurences;
  lastEventOccurences[EVENT_R] = 0;
  std::map<uint8_t, bool> eventSeen;
  eventSeen[EVENT_R] = true;

  //when
  bool result = TimePredicateWrapper::call(10001, &lastEventOccurences, &eventSeen, pred);

  //then
  assertTrue(result);
}