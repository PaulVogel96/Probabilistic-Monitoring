# Modeling Properties with probabilistic Automatons
The goal of this folder is to collect implementations of different atomic properties. These properties are basic patterns, from which more complex monitors can/should be constructed. Properties are inspired by: https://github.com/hub-se/PSP-UPPAAL/wiki/State-based-Specification-Patterns-for-UPPAAL

The idea is to model these properties while modeling different types of uncertainty.

## What types of Monitors are needed?

### Problem with Properties which need to be observed multiple times  
Currently we instantiate one Automaton per event stream. But there exist properties which can potentially trigger everytime something happens is reached
- "after any Q, P holds"
- "Before any R, P holds"

Atm we are only able to model globally valid properties, such as:
- "It is always the case that P holds"
- "It is never the case that P holds"
- "After Q happens and before R happens, P holds"

=> We have a problem with expressiveness, we need to build monitors that can handle such "ordered" properties

### Do we need to be able to analyze multiple events at a time?
Common benchmarks seem to be able to handle multiple Properties at the same time. So, in a stream, at one timestamp P might either hold or not hold and R might hold or not hold at the same time.

=> Maybe we need to be able express this in our inputstreams. 

## Types of uncertainty
- Missing events
    - This is hard to model. Possibly, expect event at a certain timestamp, if it does not arrive treat as corrupted event?

- Corrupted events
    - Introduce another character to the alphabet of possible events which is symbolic for a corrupted  

- Wrongly recognized events
    - Essentially, for each transition, add another transition for each event of the alphabet with a low probability (as high as the uncertainty is)
    - So, for each incoming event, it is possibly one of the other events

- Wrongly valued events
    - Essentially, when transitions are triggered based on event value, add small probability to trigger wrong transition to model uncertainty?
    - At the moment, the engine does not handle valued events. Implement this?
        - Probably not needed. Simple character events can be understood as "valued" events. If there is a transition which fires for any B event with a value >17, then we could reinterpret any C as an B event with a value >17 and any D as a B event with a value <=17.