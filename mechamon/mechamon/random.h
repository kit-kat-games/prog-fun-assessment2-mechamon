#pragma once
#include <random>
#include <algorithm>

inline std::random_device rd;
inline std::mt19937 rng{ rd() };