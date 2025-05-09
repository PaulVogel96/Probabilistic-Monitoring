## Arduino State Machine
This repository contains code for two types of state machines implemented on Arduino:
1. **Normal State Machine:** A standard state machine for transitioning between different states based on predefined conditions.
2. **Probabilistic State Machine:** A state machine where transitions between states still depend on predefined condition but are also determined by probabilistic rules.
    Thus, each state has a certain probability to be active at any given moment.
## Requirements
  ### Extrernal Libraries
  Almost all of the libraries used for the Statemachine are already included in the Arduino IDE.
  The only external Library that needs to be installed:
  [Standart C++ for Arduino](https://github.com/maniacbug/StandardCplusplus/tree/master).
  For the installation, please refer to the instructions provided in the repository of the library.

  ### Arduino IDE Version
  Currently, the external library used for this project does not work with the most recent version of the Arduino IDE.
  To solve this issue, you will need to install an older version of "Arduino AVR Boards".
  To do this, you have to:
  1. go to your Arduino "Boards Manager"(Located in the sidebar of the IDE)
  2. for "Arduino AVR Boards" install version **1.8.2**
  3. restart you IDE
  
