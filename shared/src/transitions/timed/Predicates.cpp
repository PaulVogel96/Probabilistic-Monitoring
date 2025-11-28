#include <map>

#include <./events.hpp>
#include "Predicates.hpp"

bool pred_R_lt10(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents)
{
    auto it = lastEvents->find(EVENT_R);
    if (it == lastEvents->end()) {
        return false; 
    }
    uint32_t difference = now - it->second;
    return difference < 10000;
}

bool pred_P_did_not_happen_for_10s(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents)
{
    auto it = lastEvents->find(EVENT_P);
    if (it == lastEvents->end()) {
        return false; 
    }
    uint32_t difference = now - it->second;
    return difference >= 10000;
}

bool pred_r_happened_over_4s_ago(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents)
{
    auto it = lastEvents->find(EVENT_R);
    if (it == lastEvents->end()) {
        return false; 
    }
    uint32_t difference = now - it->second;
    return difference > 4000;
}

bool pred_r_happened_less_or_equal_than_4s_ago(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents)
{
    auto it = lastEvents->find(EVENT_R);
    if (it == lastEvents->end()) {
        return false; 
    }
    uint32_t difference = now - it->second;
    return difference <= 4000;
}

bool pred_q_happened_over_3s_ago(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents)
{
    auto it = lastEvents->find(EVENT_Q);
    if (it == lastEvents->end()) {
        return false; 
    }
    uint32_t difference = now - it->second;
    return difference > 3000;
}

bool pred_q_happened_less_or_equal_than_3s_ago(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents)
{
    auto it = lastEvents->find(EVENT_Q);
    if (it == lastEvents->end()) {
        return false; 
    }
    uint32_t difference = now - it->second;
    return difference <= 3000;
}

bool pred_x_happened_over_6s_ago(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents)
{
    auto it = lastEvents->find(EVENT_X);
    if (it == lastEvents->end()) {
        return false; 
    }
    uint32_t difference = now - it->second;
    return difference > 6000;
}

bool pred_x_happened_less_or_equal_than_6s_ago(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents)
{
    auto it = lastEvents->find(EVENT_X);
    if (it == lastEvents->end()) {
        return false; 
    }
    uint32_t difference = now - it->second;
    return difference <= 6000;
}