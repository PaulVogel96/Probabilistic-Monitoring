## Arduino State Machine
This repository contains code to run probabilistic state machines on an arduino board.
These probabilistic state machines represent a monitor for stream runtime verification.
The longterm goal of this project is to build probabilistic monitors which are able to handle multiple types of uncertainty.

## Requirements

  ### Extrernal Libraries
  Almost all of the libraries used for the Statemachine are already included in the Arduino IDE.
  From the Arduino IDE include the following libraries:
  1. List (by Niklas Kaaf), version 3.0.1
  2. Vector (by Peter Polidoro), version 1.2.2
  3. AUnit (by Brian T. Parks), version 1.2.2
  
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
  
## Tests
To run the Unit tests, either uncomment `//define TEST` or if using the Arduino CLI, compile with the flag `TEST`