# Interpreting results

## Reminder what specific Metrics mean
### Metrics:
- TP: True positives (a violation has occured and was correctly detected)
- FP: False positives (a violation has not occured but was detected)
- FN: False negatives (a violation has occured but was not predicted)
- TN: True negatives (a violation has not occured and no violation was predicted)

### Computed Metrics:
- Precision: TP / (TP + FP) Out of all flagged violations, how many were correct?
  High precision -> few false alarms, low precision -> many false alarms
- Recall: TP / (TP + FN) Out of all actual violations, how many did we detect?
  High recall -> rarely miss violations, low recall -> many actual violations missed
- F1: 2 * Precision * recall / (Precision + Recall) harmonic mean of precision and recall
  High F1 -> good overall performance, low F1 -> either low precision, recall or both
- IoU Intersection over Union: TP / (TP + FP +FN) Similar to F1, rates overall performance
  High IoU -> generally 

## Experimental setups

### proportional missing
- Data is missing completely at random (MCAR)
- a fixed percentage of data points is removed
- All Timestamps have the same probability of missing.
- Intuitively, this can be interpreted as random packet loss
- Ran experiments with missing rates: 
    - 0.05
    - 0.1
    - 0.2

### blocking missing
- Missing data occurs in contiguous blocks
- blocks do not overlap
- Overall missing rate is put into account
- L describes block length
- simulates temporary outages of sensors, connections, etc...
- Ran experiments
    - MR 0.1, L 3
    - MR 0.1, L 5
    - MR 0.1, L 10
    - MR 0.2, L 3
    - MR 0.2, L 5
    - MR 0.2, L 10

### periodic missing
- for each period, only a fraction of the data is kept
- T describes the timeperiod, keep the ratio of data that is kept (higher keep -> less missing data)
- Intuition: Something like lowered sampling rates due to power struggles, periodic communication windows or similar
- Ran experiments
    - T10 keep 0.5
    - T10 keep 0.7
    - T20 keep 0.5
    - T20 keep 0.7

### event missing
- whole columns get removed
- col-p means the whole column p is removed
- Intuition: A sensor has failed, a communication topic is not published
- ran experiments
    - col-p
    - col-r
    - col-s


## Observations
- We mainly look at values from seed2025 but will note when observations differ at seed2099
- Since we are talking about safety properties, we focus our interpretation on the detection of TP
- FP values also get looked at but are less important
- Recall is also good indicator about how good we perform
- Because in the truth trace violations are much rarer than non-violations, FP detection is much higher than TP detection
- Precision, F1 and IoU get worse the higher the threshold value for violations becomes as FP dominate the metrics
- comparisons (TP X -> Y) are generally done between the deterministic version (X) and the probabilitic version (Y)

### General observations 
- Using our probabilistic approach, we almost always catch at least the same amount of TP violations except for very high violation thresholds 
- In nearly all cases, we catch more TP violations than using the deterministic approach
- In nearly all cases we also generate more FP violations than using the regular approach
- The lower the threshold for violations is, the more TP violations we catch, but also the higher the amount of FP violations gets
- As a result, the lower the threshold for violations is set, the higher the recall becomes
- At the same time, Precision, F1 and IoU shrink, the lower the V threshold is set

### proportional missing
- probabilistic approach is okay here
- The lower the MR, the less effective our probabilistic approach becomes compared to the deterministic one (same amount of TP with MR 0.05, more FP 459 -> 796 at V threshold 0.1)
- Only At higher MR, slightly more TP are discovered (MR 0.1, Threshold 0.1, one more TP; MR 0.2, V threshold 0.1: TP 40 -> 45, Recall 0,555 -> 0.625)
- Amount of FP ~ doubles at V threshold 0.1 compared to deterministic approach

### blocking missing
- Our probabilistic approach performs well unless lower MR and L
- Amount of TP improves at any level of MR and block length
- Best improvements in TP happen at higher MR and Block length (MR 0.2, L 10, V threshold 0.1: TP 40 -> 52, recall 0.555 -> 0.722)
- Interestingly, at the highest V threshold level 0.5, we can find that for lower MR and L we detect (very slightly) less TP
  - MR 0.1 L3: TP 43 -> 42
  - MR 0.1 L5: TP 44 -> 43
- This does not happen in Seed2099
- At the same time additionally detected TP are smaller in Seed2099 but still significant (MR 0.2 L 10 V threshold 0.1: TP 42 -> 47)

### periodic missing
- this is generally the place where our approach performs best
- The lower keep is (read: the higher the missingness), the better the approach performs
- In some experimental setups TP detection is more than doubled
  - T10 keep 05 V threshold 0.1: TP 33 -> 49, recall 0,45 -> 0,68
  - T20 keep 05 V threshold 0.1: TP 24 -> 54, recall 0,33 -> 0,75
  - T20 keep 07 V threshold 0.1: TP 34 -> 49, recall 0,47 -> 0,68
- But Amount of FP also increases significantly
  - T10 keep 05 V threshold 0.1: FP 2075 -> 5727
  - T20 keep 05 V threshold 0.1: FP 1313 -> 6209
  - T20 keep 07 V threshold 0.1: FP 990 -> 3562
- Results are identical between seeds, maybe because missingness pattern is not really random

### event missing
- Here our approach, as expected, fails to improve results
- this is due to the fact that our system is only able to represent missing data rows
- missing column data can not be modeled in our system
- probabilistic automata behave as the deterministic do (because EVENT_MISSING) is never found in the trace
- treats missing data as false signals
- BUT: System does not worsen compared to deterministic approach
- instead results are identical to deterministic approach because probabilistic transitions are never fired

### P1 "every sliding window of length 20 s contains at least one p"
- This is the worst performing property out all of them
- many runs produce no TP detections at all
- if TP detection happens at all, it is very low numbers (1-10)
- out of all experimental setups, periodic missing has at least some TP detections but probabilistic and deterministic versions are identical
- consistent across seeds
- This could indicate either of two things:
  - the property is especially vulnerable to missing data
  - the automaton which we used for property detection is disfunctional
- Event missing setup: removal of col-p leads to the property declaring the whole trace as violation (for that property) -> does not work

### P2 "After each p, an r must occur within [p+1, p+3]"
- blocking missing: some differences between seeds are noticable
  - Seed2099: property sees only marginal improvements in TP detection for blocking missing
    - at most, improves TP 0 -> 3 for blocking MR 0.2 L5  V threshold 0.1, recall 0 -> 0,16
  - Seed2025: property performs better compared to Seed2099
    - at most, improves TP 0 -> 7 for blocking MR 0.2 L10 V threshold 0.1, recall 0 -> 0.38
- event missing setup is disfunctional, no violation detections at all
- periodic missing sees improvements in recall and TP detection across the board
  - T10 keep 0.5 V threshold 0.1: TP 6 -> 9, recall 0.33 -> 0.5
  - T10 keep 0.7 V threshold 0.1: TP 0 -> 4, recall 0 -> 0.22
  - T20 keep 0.5 V threshold 0.1: TP 2 -> 12, recall 0.11 -> 0.66
- proportional missing only really sees significant improvements of TP detection at higher MR:
  - MR 0.2 V threshold 0.1: TP 1 -> 6, recall 0.05 -> 0.33

### P3 "After each r, s must hold continuously at the three samples {r, r+1, r+2}"
- results similar across seeds
- Generally, this property has very high recall over all missingness setups and runs
- The deterministic version already has high recall values
- Probabilistic version with lower V threshold (0.1 - 0.3) does achieve recall of 1 (identified all TP violations) in many cases where deterministic version did not
- But FP detection increases significantly in probabilistic version
- blocking missing: 
  - deterministic version achieves perfect recall of 1 in 2/6 experiments
  - probabilistic version achieves perfect recall in 6/6 experiments
  - this is consistent with seed2099 (only deterministic version performed slightly worse there)
- event missing performs identical to determinsitic version, does not detect anything on col-r experiment, perfect detection on other experiment though 
- periodic missing:
  - improve TP detection in 3/4 experiments, last one TP detection is the same as deterministic version
    - T20 keep 0.5 V threshold 0.1: TP: 5 -> 12, recall 0.41 -> 1, FP 18 -> 1657
    - T20 keep 0.7 V threshold 0.1: TP: 8 -> 12, recall 0.66 -> 1, FP 32 -> 942
- proportional missing:
  - deterministic version already detected most TP violations:
    - MR 0.05: TP 12, recall 1, FP 27
    - MR 0.1: TP 12, recall 1, FP 28
    - MR 0.2: TP 10, recall 0.83, FP 24
  - probabilistic version catches identical TPs but produces slightly more FP
    - MR 0.05, V threshold 0.1: TP 12, recall 1, FP 92
    - MR 0.1, V threshold 0.1: TP 12, recall 1, FP 157
    - MR 0.2, V threshold 0.1: TP 12, recall 0.83, FP 317
    - this is actually the first time that lower V threshold performs better, as the same amount of TP are catched, while FP are lower

### P4 " (i.e., no p triggers inside any s-true window)"
- again FP rate significantly up
- results over seeds are similar
- blocking missing: property barely outperforms deterministic version
  - only slight improvements in TP over all blocking missing setups
  - BUT: deterministic version already performs very good with all 6 experimental setups recall > 0.75 and 5/6 recall > 0.9
  - Violation threshold 0.1 achieves perfect recall of 1 in 4/6 runs and improves the other two
- event missing: identical to deterministic, fails on either col-s or col-p missing, perfect recall on col-r
- periodc missing:
  - significant improvements in 3/4 experiments:
    - T10 keep 0.5 V threshold 0.1: TP 18 -> 27, recall 0.5 -> 0.75, FP 14 -> 719
    - T20 keep 0.5 V threshold 0.1: TP 14 -> 30, recall 0.38 -> 0.83, FP 10 -> 1247
    - T20 keep 0.7 V threshold 0.1: TP 21 -> 31, recall 0.58 -> 0.86, FP 6 -> 533
- periodic missing:
  - no improvement compared to deterministic version, TP identical
  - FP also barely up, ONLY in v threshold 0.1 in 1 experiment FP: 4 -> 7
  - higher v thresholds (0.2 and up) perform identical to deterministic version
  - recall was already very high here (> 0.75 in 3/3 experiments), so improvements could be hard to achieve 

