#pragma once

#include <string>
#include <array>

namespace SLR {

enum class NonTerminals
{
    S = -1,

    E = 0,

    T = 1,

    F = 2
};

struct Rule
{
    NonTerminals LHS;          
    size_t Len;           
};

inline constexpr size_t RuleCount = 10;


inline constexpr std::array<Rule, RuleCount> Grammar =
{{
    {NonTerminals::S, 1},            // S -> E            
    {NonTerminals::E, 3},            // E -> E + T
    {NonTerminals::E, 3},            // E -> E - T
    {NonTerminals::E, 1},            // E -> T
    {NonTerminals::T, 3},            // T -> T * F
    {NonTerminals::T, 3},            // T -> T / F
    {NonTerminals::T, 1},            // T -> F
    {NonTerminals::F, 3},            // F -> (E)
    {NonTerminals::F, 1},            // F -> ID
    {NonTerminals::F, 2}             // F -> -F
}};

}