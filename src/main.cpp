#include <iostream>
#include <cassert>
#include "myMath.h"

void testRotation() {
    std::cout << "=== Rotation Tests ===\n";

    const float PI = 3.14159265f;

    // 1. makeRotationX(0) — 단위행렬이어야 함
    Matrix4x4 rx0 = Matrix4x4::makeRotationX(0.0f);
    assert(nearlyEqual(rx0.m[0][0], 1.0f));
    assert(nearlyEqual(rx0.m[1][1], 1.0f));
    assert(nearlyEqual(rx0.m[2][2], 1.0f));
    assert(nearlyEqual(rx0.m[3][3], 1.0f));
    std::cout << "RotationX(0)         : PASS\n";

    // 2. makeRotationX(90도) — Y축이 Z축으로
    // row vector 기준: j(0,1,0) * R_x = (0, cos90, sin90) = (0, 0, 1)
    Matrix4x4 rx90 = Matrix4x4::makeRotationX(PI / 2.0f);
    Vector4f j(0.0f, 1.0f, 0.0f, 0.0f);
    Vector4f result = j * rx90;
    assert(nearlyEqual(result.x, 0.0f));
    assert(nearlyEqual(result.y, 0.0f));
    assert(nearlyEqual(result.z, 1.0f));
    std::cout << "RotationX(90) Y→Z    : PASS  ";
    result.print_components();

    // 3. makeRotationY(90도) — Z축이 X축으로
    // k(0,0,1) * R_y = (sin90, 0, cos90) = (1, 0, 0)
    Matrix4x4 ry90 = Matrix4x4::makeRotationY(PI / 2.0f);
    Vector4f k(0.0f, 0.0f, 1.0f, 0.0f);
    result = k * ry90;
    assert(nearlyEqual(result.x, 1.0f));
    assert(nearlyEqual(result.y, 0.0f));
    assert(nearlyEqual(result.z, 0.0f));
    std::cout << "RotationY(90) Z→X    : PASS  ";
    result.print_components();

    // 4. makeRotationZ(90도) — X축이 Y축으로
    // i(1,0,0) * R_z = (cos90, sin90, 0) = (0, 1, 0)
    Matrix4x4 rz90 = Matrix4x4::makeRotationZ(PI / 2.0f);
    Vector4f i(1.0f, 0.0f, 0.0f, 0.0f);
    result = i * rz90;
    assert(nearlyEqual(result.x, 0.0f));
    assert(nearlyEqual(result.y, 1.0f));
    assert(nearlyEqual(result.z, 0.0f));
    std::cout << "RotationZ(90) X→Y    : PASS  ";
    result.print_components();

    // 5. makeRotation — Y축 기준 90도 회전
    // makeRotationY랑 결과가 같아야 함
    Vector3f yAxis(0.0f, 1.0f, 0.0f);
    Matrix4x4 rArb = Matrix4x4::makeRotation(yAxis, PI / 2.0f);
    result = k * rArb;
    assert(nearlyEqual(result.x, 1.0f));
    assert(nearlyEqual(result.y, 0.0f));
    assert(nearlyEqual(result.z, 0.0f));
    std::cout << "makeRotation(Y, 90)  : PASS  ";
    result.print_components();

    // 6. 360도 회전 — 원래 벡터로 돌아와야 함
    Matrix4x4 rx360 = Matrix4x4::makeRotationX(2.0f * PI);
    Vector4f v(1.0f, 2.0f, 3.0f, 0.0f);
    result = v * rx360;
    assert(nearlyEqual(result.x, v.x));
    assert(nearlyEqual(result.y, v.y));
    assert(nearlyEqual(result.z, v.z));
    std::cout << "RotationX(360)       : PASS  ";
    result.print_components();

    // 7. Point(w=1)의 w값 보존
    Vector4f point(1.0f, 0.0f, 0.0f, 1.0f);
    result = point * rx90;
    assert(nearlyEqual(result.w, 1.0f));
    std::cout << "w값 보존             : PASS  ";
    result.print_components();

    std::cout << "\n모든 Rotation 테스트 통과!\n";
}

int main() {
    testRotation();
    return 0;
}