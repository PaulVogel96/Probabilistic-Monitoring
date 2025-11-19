#ifndef events_hpp
#define events_hpp

#include <stdint.h>

constexpr uint8_t EVENT_NONE = 0; //00000000 
constexpr uint8_t EVENT_P = 1 << 0; //00000001
constexpr uint8_t EVENT_S = 1 << 1; //00000010
constexpr uint8_t EVENT_Q = 1 << 2; //00000100
constexpr uint8_t EVENT_R = 1 << 3; //00001000

#endif /* events_hpp*/
