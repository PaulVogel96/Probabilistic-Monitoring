#ifndef events_hpp
#define events_hpp

#include <stdint.h>

constexpr uint8_t EVENT_NONE = 0; //00000000 
constexpr uint8_t EVENT_P = 1 << 0; //00000001
constexpr uint8_t EVENT_S = 1 << 1; //00000010
constexpr uint8_t EVENT_Q = 1 << 2; //00000100
constexpr uint8_t EVENT_R = 1 << 3; //00001000
constexpr uint8_t EVENT_N = 1 << 4; //00010000
constexpr uint8_t EVENT_X = 1 << 5; //00100000
constexpr uint8_t EVENT_Y = 1 << 6; //01000000
constexpr uint8_t EVENTS_MISSING = 1 << 7; //10000000

#endif /* events_hpp*/
