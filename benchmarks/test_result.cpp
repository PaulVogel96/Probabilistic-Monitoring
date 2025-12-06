#include "StandardCplusplus.h"
#include "vector"
#include "events.hpp"

std::vector<uint8_t> events_to_process = { 
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