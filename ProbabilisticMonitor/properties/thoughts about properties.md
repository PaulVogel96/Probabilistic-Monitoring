# Modeling Properties with probabilistic Automatons
The goal of this folder is to collect implementations of different atomic properties. These properties are basic patterns, from which more complex monitors can/should be constructed. Properties are inspired by: https://github.com/hub-se/PSP-UPPAAL/wiki/State-based-Specification-Patterns-for-UPPAAL

The idea is to model these properties while modeling different types of uncertainty.

## Types of uncertainty
- Missing events
    - This is hard to model. Possibly, expect event at a certain timestamp, if it does not arrive treat as corrupted event?

- Corrupted events
    - Introduce another character to the alphabet of possible events which is symbolic for a corrupted  

- Wrongly recognized events
    - Essentially, for each transition, add another transition for each event of the alphabet with a low probability (as high as the uncertainty is)
    - So, for each incoming event, it is possibly one of the other events

- Wrongly valued events
    - At the moment, the engine does not handle valued events. Implement this?
    - Essentially, when transitions are triggered based on event value, add small probability to trigger wrong transition to model uncertainty?