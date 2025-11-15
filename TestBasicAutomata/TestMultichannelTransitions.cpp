#include <map>
#include <AUnit.h>
#include <automatons/basic/ALoopBAutomaton.hpp>
#include <transitions/AllRequiredEventsActiveTransition.hpp>
#include <transitions/AllRequiredEventsInactiveTransition.hpp>
#include <transitions/AnyRequiredEventsActiveTransition.hpp>
#include <transitions/AnyRequiredEventsInactiveTransition.hpp>
#include <transitions/ExactEventsActiveTransition.hpp>
#include <transitions/ExactEventsInactiveTransition.hpp>
#include <transitions/MixedEventsConditionTransition.hpp>

using namespace aunit;

class TestMultichannelTransitions : public TestOnce {
  protected:
  void setup() override {}
  
  bool approxEqual(float a, float b, float epsilon = 0.0001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestMultichannelTransitions, AllRequiredEventsActiveTransition_fires_when_all_required_events_are_passed_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AllRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.shouldFire(EVENT_P);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsActiveTransition_does_not_fire_when_not_all_required_events_are_passed_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AllRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_P);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsActiveTransition_does_fire_when_all_required_events_are_passed_multiple_events) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AllRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_P | EVENT_Q);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsActiveTransition_does_not_fire_when_not_all_required_events_are_passed_multiple_events) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AllRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_P);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsActiveTransition_additional_properties_do_not_matter) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AllRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.shouldFire(EVENT_P | EVENT_Q | EVENT_R | EVENT_S);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsActiveTransition_fires_when_any_required_events_are_passed_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AnyRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.shouldFire(EVENT_P);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsActiveTransition_does_not_fire_when_none_of_required_events_are_passed_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AnyRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_P);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsActiveTransition_does_fire_when_any_required_events_are_passed_multiple_events_possible) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AnyRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_P);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsActiveTransition_does_not_fire_when_none_of_the_required_events_are_passed_multiple_events) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AnyRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_S);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsActiveTransition_additional_properties_do_not_matter) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AnyRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.shouldFire(EVENT_P | EVENT_Q | EVENT_R | EVENT_S);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, ExactEventsActiveTransition_fires_when_required_events_are_passed_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsActiveTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_Q);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, ExactEventsActiveTransition_does_not_fire_when_none_of_required_events_are_passed_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsActiveTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_P);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, ExactEventsActiveTransition_does_fire_when_exact_required_events_are_passed_multiple_events_possible) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsActiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_P | EVENT_Q);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, ExactEventsActiveTransition_does_not_fire_when_none_of_the_required_events_are_passed_multiple_events) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsActiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_S);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, ExactEventsActiveTransition_properties_leads_to_not_firing) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsActiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.shouldFire(EVENT_P | EVENT_Q | EVENT_R | EVENT_S);

  //then
  assertFalse(result);
}


testF(TestMultichannelTransitions, ExactEventsInactiveTransition_fires_when_required_events_are_not_passed_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsInactiveTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_S);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, ExactEventsInactiveTransition_does_not_fire_when_exact_events_are_passed_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsInactiveTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_Q);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, ExactEventsInactiveTransition_does_fire_when_exact_required_events_are_inactive_multiple_events_possible) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_S | EVENT_R);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, ExactEventsInactiveTransition_does_not_fire_when_only_of_the_required_events_is_inactive_multiple_events) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_P);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, ExactEventsInactiveTransition_additional_events_leads_to_not_firing) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.shouldFire(EVENT_P | EVENT_Q | EVENT_R | EVENT_S);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsInactiveTransition_fires_when_all_required_events_are_inactive_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AllRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.shouldFire(EVENT_Q | EVENT_R | EVENT_S); //Only P is not active

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsInactiveTransition_does_not_fire_when_required_inactive_event_is_passed_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AllRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.shouldFire(EVENT_P);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsInactiveTransition_does_fire_when_all_required_events_are_passed_multiple_events) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AllRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_S | EVENT_R);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsInactiveTransition_does_not_fire_when_not_all_required_events_are_inactive_multiple_events) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AllRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_P | EVENT_R | EVENT_S);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsInactiveTransition_additional_properties_can_be_inactive) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AllRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.shouldFire(EVENT_S);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsInactiveTransition_fires_when_any_of_the_required_events_are_inactive_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AnyRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.shouldFire(EVENT_Q | EVENT_R | EVENT_S); //Only P is not active

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsInactiveTransition_does_not_fire_when_required_inactive_event_is_passed_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AnyRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.shouldFire(EVENT_P);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsInactiveTransition_does_fire_when_any_of_required_events_are_inactive_but_not_all_multiple_events) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AnyRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_Q | EVENT_S | EVENT_R); //only p is inactive

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsInactiveTransition_does_fire_when_all_required_events_are_inactive_multiple_events) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AnyRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_R | EVENT_S); //P and Q inactive

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsInactiveTransition_additional_properties_can_be_inactive) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  AnyRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.shouldFire(EVENT_S); //Q and R also inactive

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, MixedEventsConditionTransition_fires) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  MixedEventsConditionTransition t1(&a, &b, 1.0, EVENT_P, EVENT_R);

  //when
  bool result = t1.shouldFire(EVENT_P); //R is inactive

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, MixedEventsConditionTransition_doesnt_fire) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  MixedEventsConditionTransition t1(&a, &b, 1.0, EVENT_P, EVENT_R);

  //when
  bool result = t1.shouldFire(EVENT_P | EVENT_R); //R is active

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, MixedEventsConditionTransition_fires_multiple_events) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  MixedEventsConditionTransition t1(&a, &b, 1.0, EVENT_P, EVENT_R);

  //when
  bool result = t1.shouldFire(EVENT_P | EVENT_Q); //R is inactive

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, MixedEventsConditionTransition_doesnt_fire_multiple_events) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  MixedEventsConditionTransition t1(&a, &b, 1.0, EVENT_P, EVENT_R);

  //when
  bool result = t1.shouldFire(EVENT_R | EVENT_Q | EVENT_S); //P is inactive

  //then
  assertFalse(result);
}
