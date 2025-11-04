constexpr uint8_t EVENT_P = 1 << 0; //00000001
constexpr uint8_t EVENT_S = 1 << 1; //00000010
constexpr uint8_t EVENT_Q = 1 << 2; //00000100
constexpr uint8_t EVENT_R = 1 << 3; //00001000

bool allRequiredEventsActive(uint8_t input, uint8_t mask){
    return (input & mask) == mask;
}

bool anyRequiredEventActive(uint8_t input, uint8_t mask){
    return (input & mask) != 0;
}

bool allEventsMatch(uint8_t input, uint8_t mask){
    return (input == mask);
}