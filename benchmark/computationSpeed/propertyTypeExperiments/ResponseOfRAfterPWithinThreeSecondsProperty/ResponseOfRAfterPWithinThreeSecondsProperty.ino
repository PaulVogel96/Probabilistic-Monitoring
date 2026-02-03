#include <List.hpp>
#include <State.hpp>
#include <ProbTransition.hpp>
#include <ProbStatemachine.hpp>
#include <automatons/properties/timed/probabilistic/ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty.hpp>
#include <Utils.hpp>
#include <traces/blocking_missing/seed2025/coupled_blocking_missing_seed2025_mr0_1_L_10.hpp>

constexpr int TRACE_LEN = 3603;
constexpr int WARMUP_RUNS = 1;
constexpr int MEASURED_RUNS = 4;

int run_idx = 0;

void run_once(bool measure) {
  ResponseOfRAfterPWithinThreeSecondsProbabilisticProperty p1;

  unsigned long t_start = micros();

  for (int i = 0; i < TRACE_LEN; ++i) {
    uint8_t event = pgm_read_byte(&coupled_blocking_missing_seed2025_mr0_1_L_10[i]);
    uint32_t timestamp = i * 1000UL;

    p1.changeStates(event, timestamp);
    volatile bool v1 = isVerdictViolated(p1.getVerdictProbabilities());
    (void)v1;
  }

  unsigned long elapsed = micros() - t_start;

  if (measure) {
    Serial.print("run=");
    Serial.print(run_idx);
    Serial.print(" elapsed_us=");
    Serial.println(elapsed);
  }
}

void setup() {
  Serial.begin(230400);
  Serial.flush();
}

void loop() {

  if (run_idx < WARMUP_RUNS + MEASURED_RUNS) {

    bool measure = (run_idx >= WARMUP_RUNS);
    run_once(measure);

    run_idx++;

  } else {
    while (true) {}
  }
}