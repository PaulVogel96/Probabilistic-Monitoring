#include <map>
#include <AUnit.h>
#include <Utils.hpp>

using namespace aunit;

class TestUtils : public TestOnce {
  protected:
  void setup() override { /* runs once */ }
  
  bool approxEqual(float a, float b, float epsilon = 0.0001) {
    return fabs(a - b) < epsilon;
  }
};

testF(TestUtils, test_argmax_false) {
  //given
  std::map<Verdict, float> verdictProbs;
  verdictProbs[Verdict::SATISFIED] = 0.7;
  verdictProbs[Verdict::VIOLATED] = 0.2;
  verdictProbs[Verdict::INCONCLUSIVE] = 0.1;

  //when
  bool result = isVerdictViolated(verdictProbs);

  //then
  assertFalse(result);
}

testF(TestUtils, test_argmax_true_edgecase) {
  //given
  std::map<Verdict, float> verdictProbs;
  verdictProbs[Verdict::SATISFIED] = 0.45;
  verdictProbs[Verdict::VIOLATED] = 0.45;
  verdictProbs[Verdict::INCONCLUSIVE] = 0.1;

  //when
  bool result = isVerdictViolated(verdictProbs);

  //then
  assertTrue(result);
}

testF(TestUtils, test_argmax_true) {
  //given
  std::map<Verdict, float> verdictProbs;
  verdictProbs[Verdict::SATISFIED] = 0.3;
  verdictProbs[Verdict::VIOLATED] = 0.6;
  verdictProbs[Verdict::INCONCLUSIVE] = 0.1;

  //when
  bool result = isVerdictViolated(verdictProbs);

  //then
  assertTrue(result);
}

testF(TestUtils, test_argmax_true_also) {
  //given
  std::map<Verdict, float> verdictProbs;
  verdictProbs[Verdict::SATISFIED] = 0.33;
  verdictProbs[Verdict::VIOLATED] = 0.34;
  verdictProbs[Verdict::INCONCLUSIVE] = 0.33;

  //when
  bool result = isVerdictViolated(verdictProbs);

  //then
  assertTrue(result);
}

testF(TestUtils, test_printing_of_result_map) {
  //given
  std::map<Verdict, float> verdictProbs;
  verdictProbs[Verdict::SATISFIED] = 0.33;
  verdictProbs[Verdict::VIOLATED] = 0.34;
  verdictProbs[Verdict::INCONCLUSIVE] = 0.33;

  //when
  String output = verdictMapToString(verdictProbs);

  //then
  assertStringCaseEqual("{S: 0.33; V: 0.34; I: 0.33}", output);
}