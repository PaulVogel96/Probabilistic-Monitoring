#include <List.hpp>
#include <State.hpp>
#include <ProbTransition.hpp>
#include <ProbStatemachine.hpp>
#include <automatons/properties/timed/ExistenceOfPWithinTenSecondsProperty.hpp>
#include <automatons/properties/timed/ExistenceOfSAfterRWithinFourSecondsProperty.hpp>
#include <automatons/properties/timed/AbsenceOfNAfterQWithinThreeSecondsProperty.hpp>
#include <automatons/properties/timed/UniversalityOfYAfterXWithinSixSecondsProperty.hpp>
#include <Utils.hpp>
#include <traces/baseline/independent_baseline.hpp>

ExistenceOfPWithinTenSecondsProperty p1;
ExistenceOfSAfterRWithinFourSecondsProperty p2;
AbsenceOfNAfterQWithinThreeSecondsProperty p3;
UniversalityOfYAfterXWithinSixSecondsProperty p4;

int events_processed = 0;
std::map<Verdict, float> verdictProbabilitiesP1;
std::map<Verdict, float> verdictProbabilitiesP2;
std::map<Verdict, float> verdictProbabilitiesP3;
std::map<Verdict, float> verdictProbabilitiesP4;

void setup() {
  Serial.begin(230400);
  Serial.flush();
  Serial.println("\"time\",\"pred_P1\",\"pred_P2\",\"pred_P3\",\"pred_P4\"");
}

void loop() {
  if (events_processed < 3603) {
    uint8_t event = pgm_read_byte(&independent_baseline[events_processed]);
    uint32_t timestamp = events_processed * 1000UL;
    
    p1.changeStates(event, timestamp);
    p2.changeStates(event, timestamp);
    p3.changeStates(event, timestamp);
    p4.changeStates(event, timestamp);

    verdictProbabilitiesP1 = p1.getVerdictProbabilities();
    verdictProbabilitiesP2 = p2.getVerdictProbabilities();
    verdictProbabilitiesP3 = p3.getVerdictProbabilities();
    verdictProbabilitiesP4 = p4.getVerdictProbabilities();

    Serial.println("\"" + String(events_processed) + "\", \"" 
    + String(isVerdictViolated(verdictProbabilitiesP1)) + "\", \""
    + String(isVerdictViolated(verdictProbabilitiesP2)) + "\", \""
    + String(isVerdictViolated(verdictProbabilitiesP3)) + "\", \""
    + String(isVerdictViolated(verdictProbabilitiesP4)) + "\"");

    events_processed += 1;
  }
}