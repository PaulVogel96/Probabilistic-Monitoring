#include <map>
#include <AUnit.h>
#include <automatons/properties/untimed/order/UntilProperty/UntilProperty.cpp>
#include <automatons/properties/untimed/order/UntilProperty/UntilBeforeRProperty.cpp>
#include <automatons/properties/untimed/order/UntilProperty/UntilAfterQProperty.cpp>
#include <automatons/properties/untimed/order/UntilProperty/UntilBetweenQAndRProperty.cpp>

using namespace aunit;

class TestUntilProperty : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEquals(float a, float b, float epsilon = 0.01) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestUntilProperty, UntilProperty_satisfied) {
  //given
  UntilProperty automaton;

  //when
  automaton.processEvents("PSXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.99));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.01));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.00));
}

testF(TestUntilProperty, UntilProperty_inconclusive) {
  //given
  UntilProperty automaton;

  //when
  automaton.processEvents("PPPXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilBeforeRProperty_satisfied_when_PS_before_R) {
  //given
  UntilBeforeRProperty automaton;

  //when
  automaton.processEvents("PPSRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.98));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.02));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilBeforeRProperty_violated_when_no_SP_or_R) {
  //given
  UntilBeforeRProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilBeforeRProperty_satisfied_multiple_repetitions) {
  //given
  UntilBeforeRProperty automaton;

  //when
  automaton.processEvents("PPPPPSRXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.95));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.05));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilAfterQProperty_violated_just_q) {
  //given
  UntilAfterQProperty automaton;

  //when
  automaton.processEvents("XXQXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilAfterQProperty_satisfied) {
  //given
  UntilAfterQProperty automaton;

  //when
  automaton.processEvents("PPXQPPPPPSXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.95));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.05));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilAfterQProperty_satisfied_when_no_P_or_S_or_Q) {
  //given
  UntilAfterQProperty automaton;

  //when
  automaton.processEvents("XXXXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilAfterQProperty_inconclusive_when_no_S) {
  //given
  UntilAfterQProperty automaton;

  //when
  automaton.processEvents("XXXQPPPPPP");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.06));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.94));
}

testF(TestUntilProperty, UntilBetweenQAndRProperty_satisfied) {
  //given
  UntilBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQPSRXXQRXXQPPPSRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.00));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilBetweenQAndRProperty_satisfied_no_Q) {
  //given
  UntilBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXXRXXXSPSPSPSX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 1.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 0.0));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}

testF(TestUntilProperty, UntilBetweenQAndRProperty_violated_P_interrupted_before_S) {
  //given
  UntilBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQPPXSRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}


testF(TestUntilProperty, UntilBetweenQAndRProperty_violated_no_S) {
  //given
  UntilBetweenQAndRProperty automaton;

  //when
  automaton.processEvents("XXQPPPPRXX");
  std::map<Verdict, float> results = automaton.getVerdictProbabilities();

  //then
  assertTrue(approxEquals(results[Verdict::SATISFIED], 0.0));
  assertTrue(approxEquals(results[Verdict::VIOLATED], 1.00));
  assertTrue(approxEquals(results[Verdict::INCONCLUSIVE], 0.0));
}