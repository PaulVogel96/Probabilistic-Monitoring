1. How should properties react when violation occurs? Return to initial State or stay in violated state?
-> return to initial state and continuous evaluation -> exit violated status when new p enters

2. "All tools must use: the same NaN for missing data" -> what does this mean? If we import all traces into variables for usage and use our own event encoding, does this matter?

No, I can just map it to my internal representation

3. "Property output: For each Timestamp output the properties as described." -> At a certain timestamp system will output "violation status". How to bring this together? 

- Pick the class with the highest probability:
- if P(violation) highest -> violation
- if P(satisfied) highest -> OK
- if P(inconclusive) highest -> treat as non-violation (or NaN)

4. Why do the properties look different between Formal Constraints & TeSSLA specification?