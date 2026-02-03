#include <math.h>
#include <float.h>

#include <List.hpp>
#include <State.hpp>
#include <ProbTransition.hpp>
#include <ProbStatemachine.hpp>
#include <automatons/properties/timed/probabilistic/ExistenceOfPWithinTwentySecondsProbabilisticProperty.hpp>
#include <transitions/untimed/AllRequiredEventsActiveTransition.hpp>
#include <Utils.hpp>
#include <traces/blocking_missing/seed2025/coupled_blocking_missing_seed2025_mr0_2_L_10.hpp>

ExistenceOfPWithinTwentySecondsProbabilisticProperty p1;
std::map<Verdict, float> verdictProbabilitiesP1;

static const int N = 3603;
static const int PRINT_EVERY = 200;

int events_processed = 0;
bool donePrinted = false;

float maxAbsErr = 0.0f;
float minErr = FLT_MAX;
float maxErr = -FLT_MAX;

float minP = FLT_MAX;
float maxP = -FLT_MAX;

void setup() {
  Serial.begin(230400);
  Serial.flush();
}

void loop() {
  if (events_processed == 0) {
    Serial.println("start");
  }

  if (events_processed < N) {
    uint8_t event = pgm_read_byte(&coupled_blocking_missing_seed2025_mr0_2_L_10[events_processed]);
    uint32_t timestamp = (uint32_t)events_processed * 1000UL;

    p1.changeStates(event, timestamp);

    verdictProbabilitiesP1 = p1.getVerdictProbabilities();

    float s = verdictProbabilitiesP1[Verdict::SATISFIED];
    float i = verdictProbabilitiesP1[Verdict::INCONCLUSIVE];
    float v = verdictProbabilitiesP1[Verdict::VIOLATED];

    if (s < minP) minP = s;
    if (i < minP) minP = i;
    if (v < minP) minP = v;

    if (s > maxP) maxP = s;
    if (i > maxP) maxP = i;
    if (v > maxP) maxP = v;

    float sum = s + i + v;
    float err = sum - 1.0f;
    float absErr = fabsf(err);

    if (absErr > maxAbsErr) maxAbsErr = absErr;
    if (err < minErr) minErr = err;
    if (err > maxErr) maxErr = err;

    if ((events_processed % PRINT_EVERY) == 0) {
      Serial.print("i=");
      Serial.print(events_processed);
      Serial.print(" s=");
      Serial.print(s, 10);
      Serial.print(" i=");
      Serial.print(i, 10);
      Serial.print(" v=");
      Serial.print(v, 10);
      Serial.print(" sum=");
      Serial.print(sum, 10);
      Serial.print(" err=");
      Serial.println(err, 10);
    }

    events_processed++;
  }

  if (!donePrinted && events_processed >= N) {
    donePrinted = true;
    Serial.println("stop");
    Serial.print("maxAbsErr = ");
    Serial.println(maxAbsErr, 10);
    Serial.print("minErr = ");
    Serial.println(minErr, 10);
    Serial.print("maxErr = ");
    Serial.println(maxErr, 10);
    Serial.print("minVerdictProb = ");
    Serial.println(minP, 10);
    Serial.print("maxVerdictProb = ");
    Serial.println(maxP, 10);
  }
}