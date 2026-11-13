#pragma once
#include <random>

random_device rd;
mt19937 rng{ rd() };