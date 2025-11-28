#ifndef Predicates_hpp
#define Predcates_hpp

#include <map>

#include <./events.hpp>

bool pred_R_lt10(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents);
bool pred_P_did_not_happen_for_10s(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents);

bool pred_r_happened_over_4s_ago(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents);
bool pred_r_happened_less_or_equal_than_4s_ago(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents);

bool pred_q_happened_over_3s_ago(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents);
bool pred_q_happened_less_or_equal_than_3s_ago(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents);

bool pred_x_happened_over_6s_ago(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents);
bool pred_x_happened_less_or_equal_than_6s_ago(uint32_t now, const std::map<uint8_t, uint32_t>* lastEvents);
#endif