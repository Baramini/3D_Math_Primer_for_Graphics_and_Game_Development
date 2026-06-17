#pragma once
#include <cmath>
#include <algorithm>

inline const float PI = (float)(std::acos(-1.0)); 

// compare float value to eps
inline bool nearlyEqual(float a, float b, float eps = 1e-4f) {
    return std::abs(a - b) < eps;
}