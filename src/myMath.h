// myMath.h
#pragma once

#include <iostream>
#include <type_traits>
#include "mathUtils.h"

#include "vector2.h"
#include "Vector3.h"
#include "vector4.h"

#include "matrix4x4.h"

#include "testUtils.h"

Vector4f operator*(const Vector4f& vec, const Matrix4x4& mat) {
    Vector4f result(0.0f, 0.0f, 0.0f, 0.0f);
    result.x += (vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + vec.w * mat.m[3][0]);
    result.y += (vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + vec.w * mat.m[3][1]);
    result.z += (vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + vec.w * mat.m[3][2]);
    result.w += (vec.x * mat.m[0][3] + vec.y * mat.m[1][3] + vec.z * mat.m[2][3] + vec.w * mat.m[3][3]);

    return result;
}

//coordinateSystem.h
struct CoordinateSpace {
    Vector3f right;      // x-axis basis vector
    Vector3f up;         // y-axis basis vector
    Vector3f forward;    // z-axis basis vector
    Vector3f origin;     // point

    CoordinateSpace(float x, float y, float z) : right(1.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f), forward(0.0f, 0.0f, 1.0f), origin(x, y, z) {}

    bool isOrthgnormal() const {
        bool isUnit = nearlyEqual(right.length(), 1.0f) && nearlyEqual(up.length(), 1.0f) && nearlyEqual(forward.length(), 1.0f);
        bool isPerpendicular = nearlyEqual(right.dot(up), 0.0f) && nearlyEqual(up.dot(forward), 0.0f) && nearlyEqual(forward.dot(right), 0.0f);
        return (isUnit && isPerpendicular);
    }
    Vector3f localToWorld(const Vector3f& localPos) const { 
        return origin
        + right   * localPos.x
        + up      * localPos.y
        + forward * localPos.z;
    }
    Vector3f worldToLocal(const Vector3f& worldPos) const {  
        Vector3f d = worldPos - origin;
        return Vector3f(
            d.dot(right),
            d.dot(up),
            d.dot(forward)
        );
    }
};

const CoordinateSpace worldSpace(0.0f, 0.0f, 0.0f);