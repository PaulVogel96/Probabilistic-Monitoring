#ifndef TEST_HPP
#define TEST_HPP

#include "events.hpp"

const uint8_t test[] PROGMEM = { 
  EVENT_P, 
  EVENT_NONE, 
  EVENT_R | EVENT_S, 
  EVENT_S, 
  EVENT_S, 
  EVENT_NONE, 
  EVENT_NONE, 
  EVENT_NONE, 
  EVENT_P, 
  EVENT_NONE, 
  EVENT_R | EVENT_S 
};
#endif