#pragma once

#include <string>
#include <array>

namespace SLR {

struct Rule
{
    int LHS;           // Left Hand Side - код нетерминала слева
    int len;           // Длина правой части, сколько символов удалять
};

inline constexpr int RuleCount = 10;


inline constexpr std::array<Rule, RuleCount> grammar =
{{
    {0, 0},            // S -> E            
    {7, 3},            // E -> E + T
    {7, 3},            // E -> E - T
    {7, 1},            // E -> T
    {8, 3},            // T -> T * F
    {8, 3},            // T -> T / F
    {8, 1},            // T -> F
    {9, 3},            // F -> (E)
    {9, 1},            // F -> ID
    {9, 2}             // F -> -F
}};

}