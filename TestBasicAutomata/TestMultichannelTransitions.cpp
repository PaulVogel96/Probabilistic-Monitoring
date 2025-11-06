#include <map>
#include <AUnit.h>
#include <automatons/basic/ALoopBAutomaton.hpp>
#include <transitions/AllRequiredEventsActiveTransition.hpp>
#include <transitions/AnyRequiredEventsActiveTransition.hpp>
#include <transitions/ExactEventsMatchTransition.hpp>

using namespace aunit;

class TestMultichannelTransitions : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
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

testF(TestMultichannelTransitions, ExactEventsMatchTransition_fires_when_required_events_are_passed_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsMatchTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_Q);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, ExactEventsMatchTransition_does_not_fire_when_none_of_required_events_are_passed_single_event) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsMatchTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_P);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, ExactEventsMatchTransition_does_fire_when_exact_required_events_are_passed_multiple_events_possible) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsMatchTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_P | EVENT_Q);

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, ExactEventsMatchTransition_does_not_fire_when_none_of_the_required_events_are_passed_multiple_events) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsMatchTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.shouldFire(EVENT_S);

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, ExactEventsMatchTransition_properties_leads_to_not_firing) {
  //given
  State<ProbTransition> a("A", Verdict::INCONCLUSIVE);
  State<ProbTransition> b("B", Verdict::SATISFIED);
  ExactEventsMatchTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.shouldFire(EVENT_P | EVENT_Q | EVENT_R | EVENT_S);

  //then
  assertFalse(result);
}