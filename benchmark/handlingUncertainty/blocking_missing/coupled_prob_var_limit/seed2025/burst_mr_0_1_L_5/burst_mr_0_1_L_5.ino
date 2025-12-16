#include <List.hpp>
#include <State.hpp>
#include <ProbTransition.hpp>
#include <ProbStatemachine.hpp>
#include <automatons/properties/timed/probabilistic/ExistenceOfPWithinTwentySecondsProbabilisticProperty.hpp>
#include <automatons/properties/timed/probabilistic/ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty.hpp>
#include <automatons/properties/timed/probabilistic/UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty.hpp>
#include <automatons/properties/timed/probabilistic/MutualExclusionOfPAndSProbabilisticProperty.hpp>
#include <transitions/untimed/AllRequiredEventsActiveTransition.hpp>
#include <Utils.hpp>
#include <traces/blocking_missing/seed2025/coupled_blocking_missing_seed2025_mr0_1_L_5.hpp>

ExistenceOfPWithinTwentySecondsProbabilisticProperty p1;
ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty p2;
UniversalityOfSAfterRWithinThreeSecondsProbabilisticProperty p3;
MutualExclusionOfPAndSProbabilisticProperty p4;

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
    uint8_t event = pgm_read_byte(&coupled_blocking_missing_seed2025_mr0_1_L_5[events_processed]);
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
    + verdictMapToString(verdictProbabilitiesP1) + "\", \""
    + verdictMapToString(verdictProbabilitiesP2) + "\", \""
    + verdictMapToString(verdictProbabilitiesP3) + "\", \""
    + verdictMapToString(verdictProbabilitiesP4) + "\"");

    events_processed += 1;
  }
}
