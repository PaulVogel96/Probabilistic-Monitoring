#include <AUnit.h>

#include <State.hpp>
#include <automatons/basic/ALoopBAutomaton.hpp>
#include <transitions/untimed/AllRequiredEventsActiveTransition.hpp>
#include <transitions/untimed/AllRequiredEventsInactiveTransition.hpp>
#include <transitions/untimed/AnyRequiredEventsActiveTransition.hpp>
#include <transitions/untimed/AnyRequiredEventsInactiveTransition.hpp>
#include <transitions/untimed/ExactEventsActiveTransition.hpp>
#include <transitions/untimed/ExactEventsInactiveTransition.hpp>
#include <transitions/untimed/MixedEventsConditionTransition.hpp>

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
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AllRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.evaluate(EVENT_P, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsActiveTransition_does_not_fire_when_not_all_required_events_are_passed_single_event) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AllRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_P, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsActiveTransition_does_fire_when_all_required_events_are_passed_multiple_events) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AllRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_P | EVENT_Q, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsActiveTransition_does_not_fire_when_not_all_required_events_are_passed_multiple_events) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AllRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_P, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsActiveTransition_additional_properties_do_not_matter) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AllRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.evaluate(EVENT_P | EVENT_Q | EVENT_R | EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsActiveTransition_fires_when_any_required_events_are_passed_single_event) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AnyRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.evaluate(EVENT_P, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsActiveTransition_does_not_fire_when_none_of_required_events_are_passed_single_event) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AnyRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_P, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsActiveTransition_does_fire_when_any_required_events_are_passed_multiple_events_possible) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AnyRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_P, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsActiveTransition_does_not_fire_when_none_of_the_required_events_are_passed_multiple_events) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AnyRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsActiveTransition_additional_properties_do_not_matter) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AnyRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.evaluate(EVENT_P | EVENT_Q | EVENT_R | EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, ExactEventsActiveTransition_fires_when_required_events_are_passed_single_event) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  ExactEventsActiveTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_Q, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, ExactEventsActiveTransition_does_not_fire_when_none_of_required_events_are_passed_single_event) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  ExactEventsActiveTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_P, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, ExactEventsActiveTransition_does_fire_when_exact_required_events_are_passed_multiple_events_possible) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  ExactEventsActiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_P | EVENT_Q, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, ExactEventsActiveTransition_does_not_fire_when_none_of_the_required_events_are_passed_multiple_events) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  ExactEventsActiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, ExactEventsActiveTransition_properties_leads_to_not_firing) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  ExactEventsActiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.evaluate(EVENT_P | EVENT_Q | EVENT_R | EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertFalse(result);
}


testF(TestMultichannelTransitions, ExactEventsInactiveTransition_fires_when_required_events_are_not_passed_single_event) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  ExactEventsInactiveTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, ExactEventsInactiveTransition_does_not_fire_when_exact_events_are_passed_single_event) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  ExactEventsInactiveTransition t1(&a, &b, 1.0, EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_Q, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, ExactEventsInactiveTransition_does_fire_when_exact_required_events_are_inactive_multiple_events_possible) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  ExactEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_S | EVENT_R, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, ExactEventsInactiveTransition_does_not_fire_when_only_of_the_required_events_is_inactive_multiple_events) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  ExactEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_P, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, ExactEventsInactiveTransition_additional_events_leads_to_not_firing) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  ExactEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.evaluate(EVENT_P | EVENT_Q | EVENT_R | EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsInactiveTransition_fires_when_all_required_events_are_inactive_single_event) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AllRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.evaluate(EVENT_Q | EVENT_R | EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()); //Only P is not active

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsInactiveTransition_does_not_fire_when_required_inactive_event_is_passed_single_event) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AllRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.evaluate(EVENT_P, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsInactiveTransition_does_fire_when_all_required_events_are_passed_multiple_events) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AllRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_S | EVENT_R, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsInactiveTransition_does_not_fire_when_not_all_required_events_are_inactive_multiple_events) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AllRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_P | EVENT_R | EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AllRequiredEventsInactiveTransition_additional_properties_can_be_inactive) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AllRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.evaluate(EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsInactiveTransition_fires_when_any_of_the_required_events_are_inactive_single_event) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AnyRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.evaluate(EVENT_Q | EVENT_R | EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()); //Only P is not active

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsInactiveTransition_does_not_fire_when_required_inactive_event_is_passed_single_event) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AnyRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.evaluate(EVENT_P, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>());

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsInactiveTransition_does_fire_when_any_of_required_events_are_inactive_but_not_all_multiple_events) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AnyRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_Q | EVENT_S | EVENT_R, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()); //only p is inactive

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsInactiveTransition_does_fire_when_all_required_events_are_inactive_multiple_events) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AnyRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P | EVENT_Q);

  //when
  bool result = t1.evaluate(EVENT_R | EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()); //P and Q inactive

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, AnyRequiredEventsInactiveTransition_additional_properties_can_be_inactive) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AnyRequiredEventsInactiveTransition t1(&a, &b, 1.0, EVENT_P);

  //when
  bool result = t1.evaluate(EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()); //Q and R also inactive

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, MixedEventsConditionTransition_fires) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  MixedEventsConditionTransition t1(&a, &b, 1.0, EVENT_P, EVENT_R);

  //when
  bool result = t1.evaluate(EVENT_P, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()); //R is inactive

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, MixedEventsConditionTransition_doesnt_fire) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  MixedEventsConditionTransition t1(&a, &b, 1.0, EVENT_P, EVENT_R);

  //when
  bool result = t1.evaluate(EVENT_P | EVENT_R, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()); //R is active

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, MixedEventsConditionTransition_fires_multiple_events) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  MixedEventsConditionTransition t1(&a, &b, 1.0, EVENT_P, EVENT_R);

  //when
  bool result = t1.evaluate(EVENT_P | EVENT_Q, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()); //R is inactive

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, MixedEventsConditionTransition_doesnt_fire_multiple_events) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  MixedEventsConditionTransition t1(&a, &b, 1.0, EVENT_P, EVENT_R);

  //when
  bool result = t1.evaluate(EVENT_R | EVENT_Q | EVENT_S, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()); //P is inactive

  //then
  assertFalse(result);
}

testF(TestMultichannelTransitions, EVENTS_MISSING_triggers_explicit_transitions) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AllRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENTS_MISSING);

  //when
  bool result = t1.evaluate(EVENTS_MISSING, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()); //P is inactive

  //then
  assertTrue(result);
}

testF(TestMultichannelTransitions, EVENTS_MISSING_triggers_no_other_transitions) {
  //given
  State a("A", Verdict::INCONCLUSIVE);
  State b("B", Verdict::SATISFIED);
  AllRequiredEventsActiveTransition t1(&a, &b, 1.0, EVENT_P);
  AllRequiredEventsInactiveTransition t2(&a, &b, 1.0, EVENT_P);
  AnyRequiredEventsActiveTransition t3(&a, &b, 1.0, EVENT_P);
  AnyRequiredEventsInactiveTransition t4(&a, &b, 1.0, EVENT_P);
  ExactEventsActiveTransition t5(&a, &b, 1.0, EVENT_P);
  ExactEventsInactiveTransition t6(&a, &b, 1.0, EVENT_P);
  MixedEventsConditionTransition t7(&a, &b, 1.0, EVENT_P, EVENT_Q);

  //when
  //then
  assertFalse(t1.evaluate(EVENTS_MISSING, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()));
  assertFalse(t2.evaluate(EVENTS_MISSING, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()));
  assertFalse(t3.evaluate(EVENTS_MISSING, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()));
  assertFalse(t4.evaluate(EVENTS_MISSING, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()));
  assertFalse(t5.evaluate(EVENTS_MISSING, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()));
  assertFalse(t6.evaluate(EVENTS_MISSING, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()));
  assertFalse(t7.evaluate(EVENTS_MISSING, {0}, new std::map<uint8_t, uint32_t>(), new std::map<uint8_t, bool>()));
}

