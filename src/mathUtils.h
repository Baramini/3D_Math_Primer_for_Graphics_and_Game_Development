#pragma once
#include <cmath>
#include <algorithm>

// 부동소수점 비교
inline bool nearlyEqual(float a, float b, float eps = 1e-4f) {
    return std::abs(a - b) < eps;
}