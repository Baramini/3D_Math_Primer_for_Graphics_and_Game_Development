// myMath.h
#pragma once

#include <iostream>
#include <type_traits>
#include "mathUtils.h"

#include "vector2.h"
#include "vector3.h"

//coordinateSystem.h
struct CoordinateSpace {
    Vector3<float> right;      // x-axis basis vector
    Vector3<float> up;         // y-axis basis vector
    Vector3<float> forward;    // z-axis basis vector
    Vector3<float> origin;     // point

    CoordinateSpace(float x, float y, float z) : right(1.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f), forward(0.0f, 0.0f, 1.0f), origin(x, y, z) {}

    bool isOrthgonal() const {
        bool isUnit = nearlyEqual(right.length(), 1.0f) && nearlyEqual(up.length(), 1.0f) && nearlyEqual(forward.length(), 1.0f);
        bool isPerpendicular = nearlyEqual(right.dot(up), 0.0f) && nearlyEqual(up.dot(forward), 0.0f) && nearlyEqual(forward.dot(right), 0.0f);
        return (isUnit && isPerpendicular);
    }
    Vector3<float> localToWorld(const Vector3<float>& localPos) const { 
        return origin
        + right   * localPos.x
        + up      * localPos.y
        + forward * localPos.z;
    }
    Vector3<float> worldToLocal(const Vector3<float>& worldPos) const {  
        Vector3<float> d = worldPos - origin;
        return Vector3<float>(
            d.dot(right),
            d.dot(up),
            d.dot(forward)
        );
    }
};

const CoordinateSpace worldSpace(0.0f, 0.0f, 0.0f);