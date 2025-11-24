#ifndef Predicates_hpp
#define Predcates_hpp

#include <map>

#include <./events.hpp>

bool pred_R_lt10(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents)
{
    auto it = lastEvents->find(EVENT_R);
    if (it == lastEvents->end()) {
        return false; 
    }
    uint32_t dtR = now - it->second;

    return dtR < 10000;
}

#endif