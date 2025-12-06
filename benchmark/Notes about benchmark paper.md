# Notes about "Does Runtime Verification work with missing data?"

## 1. Introduction

### 1.4 Scope and Methods

#### Tools
Paper compares TeSSLa and RTLola

##### Benchmarks
- Independent benchmark. Missingness in one channel is independent from others
- Coupled benchmark: Missingness in one channel affects the other channel as well
- Unified 1Hz grid: All traces are aligned on discrete Timestamps at 1Hz
- Closed Interval Boundaries: Time windows like [t−5, t] include both endpoints

#### Missingness
4 types of missing data are injected into the traces:
1. Proportional / MMissing Completely at random (MCAR): Random thinning of events, e.g. 30 %  missing 
2. Periodic missing data: e.g. every second/third event
3. Burst /Block Missingness: long consecutive gaps, parameters: overall missing rate, block length
4. Column wise: All events of one type are missing (e.g. no P events)

For reproducibility, I must use the same seeds -> Should be the case if I use the same traces?

#### Truth and alignement
TP = violation correctly detected
FP = violation falsely detected
FN = violation missed
TN = non-violation correctly detected (less important)

- First, clean run is running to check spec equivalence (all tools produce same output)

##### unified NaN encoding / missing data:
- NaN is the same for missing Data?
- synchronized Stream names

##### Align outputs by “timestamp × property”
Outputs must be aligned like this:
| timestamp | property P1 output | property P2 output | … |

#### Metrics
Metrics which are calculated:
1. Precision (How many triggered violations were actually correct?) 
TP / (TP + FP)

2. Recall (How many true violations did the monitor detect?)
TP / (TP + FN)

3. F1 Score: Harmonic mean of precision and recall

4. Jaccard / IoU (Intersection-over-Union of violations sets)
measures how much the violation timestamps overlap with the ground truth
-> 1 = perfect, 0 = no overlap at all

#### Pipeline
This describes the general workflow of the project

1. Input preparation (apply missingness masks using deterministic seeds), produce multiple versions of the same trace (one per missingess type/parameter)
2. Tool execution (run traces in TeSSLa nad RTLola)
3. Normalization: Convert tool output to unified format
4. Compare each timestamp and extract classification metrics
5. Visualization using line plots, heatmaps and grouped bar charts
6. Statistical summaries

### 1.5 Main empirical findings

#### Burst/Block
TeSSLa results degrade with a higher percentage of missing data
RTLola is basically completely false all the time

#### Factors
TeSSLA mostly degrades depending on the rate of lost data, how it is missing (randomly, long blocks, shorts blocks) does not matter
-> Try to replicate this

#### Metrics
“TN mass inflates accuracy; IoU penalizes FP & FN and better reflects positive-class alignment.”
- most of the timestamps will always be non-violations
- evaluate behavior on violation relevant timestamps
-> Use the same metrics in my evaluation

## Related Work
Related Literature

## Methodology
- automatons are evaluated independently from each other
- The coupled properties receive the same input trace while the independent properties receive different input traces


