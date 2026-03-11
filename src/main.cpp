#include <iostream>
#include <cassert>
#include <cmath>
#include "myMath.h"

// 부동소수점 비교용 헬퍼
bool nearlyEqual(float a, float b, float eps = 1e-4f) {
    return std::abs(a - b) < eps;
}

void testVector3() {
    std::cout << "=== Vector3 Tests ===\n";

    // 기본 생성
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(4.0f, 5.0f, 6.0f);

    // operator+
    auto add = a + b;
    assert(nearlyEqual(add.x, 5.0f) && nearlyEqual(add.y, 7.0f) && nearlyEqual(add.z, 9.0f));
    std::cout << "operator+     : PASS  ";
    add.print_components();

    // operator-
    auto sub = a - b;
    assert(nearlyEqual(sub.x, -3.0f) && nearlyEqual(sub.y, -3.0f) && nearlyEqual(sub.z, -3.0f));
    std::cout << "operator-     : PASS  ";
    sub.print_components();

    // operator* (scalar)
    auto mul = a * 2.0f;
    assert(nearlyEqual(mul.x, 2.0f) && nearlyEqual(mul.y, 4.0f) && nearlyEqual(mul.z, 6.0f));
    std::cout << "operator*     : PASS  ";
    mul.print_components();

    // operator- (unary)
    auto neg = -a;
    assert(nearlyEqual(neg.x, -1.0f) && nearlyEqual(neg.y, -2.0f) && nearlyEqual(neg.z, -3.0f));
    std::cout << "operator-(neg): PASS  ";
    neg.print_components();

    // dot
    // (1*4 + 2*5 + 3*6 = 32)
    auto d = a.dot(b);
    assert(nearlyEqual(d, 32.0f));
    std::cout << "dot           : PASS  " << d << "\n";

    // cross
    // a(1,2,3) x b(4,5,6) = (-3, 6, -3)
    auto c = a.cross(b);
    assert(nearlyEqual(c.x, -3.0f) && nearlyEqual(c.y, 6.0f) && nearlyEqual(c.z, -3.0f));
    std::cout << "cross         : PASS  ";
    c.print_components();

    // length
    // (1,0,0) 길이는 1
    Vector3 unit(1.0f, 0.0f, 0.0f);
    assert(nearlyEqual(unit.length(), 1.0f));
    std::cout << "length        : PASS  " << a.length() << "\n";

    // normalize
    auto n = a.normalize();
    assert(nearlyEqual(n.length(), 1.0f));
    std::cout << "normalize     : PASS  ";
    n.print_components();

    // cosAngle
    // 같은 벡터끼리 → cos(0) = 1
    assert(nearlyEqual(a.cosAngle(a), 1.0f));
    // 수직 벡터 → cos(90) = 0
    Vector3 x_axis(1.0f, 0.0f, 0.0f);
    Vector3 y_axis(0.0f, 1.0f, 0.0f);
    assert(nearlyEqual(x_axis.cosAngle(y_axis), 0.0f));
    std::cout << "cosAngle      : PASS  " << a.cosAngle(b) << "\n";

    // sinAngle
    // 같은 벡터끼리 → sin(0) = 0
    assert(nearlyEqual(a.sinAngle(a), 0.0f));
    // 수직 벡터 → sin(90) = 1
    assert(nearlyEqual(x_axis.sinAngle(y_axis), 1.0f));
    std::cout << "sinAngle      : PASS  " << a.sinAngle(b) << "\n";

    // lerp
    Vector3 start(0.0f, 0.0f, 0.0f);
    Vector3 end(10.0f, 10.0f, 10.0f);
    auto mid = start.lerp(end, 0.5f);
    assert(nearlyEqual(mid.x, 5.0f) && nearlyEqual(mid.y, 5.0f) && nearlyEqual(mid.z, 5.0f));
    std::cout << "lerp          : PASS  ";
    mid.print_components();

    // lerpClamp (t > 1 클램프 확인)
    auto clamped = start.lerpClamp(end, 2.0f);
    assert(nearlyEqual(clamped.x, 10.0f));
    std::cout << "lerpClamp     : PASS  ";
    clamped.print_components();

    // distance
    Vector3 p1(0.0f, 0.0f, 0.0f);
    Vector3 p2(3.0f, 4.0f, 0.0f);
    assert(nearlyEqual(p1.distance(p2), 5.0f));
    std::cout << "distance      : PASS  " << p1.distance(p2) << "\n";

    std::cout << "\n모든 Vector3 테스트 통과!\n\n";
}

void testVector2() {
    std::cout << "=== Vector2 Tests ===\n";

    Vector2 a(1.0f, 0.0f);
    Vector2 b(0.0f, 1.0f);

    // cross (2D) — 수직이면 1
    assert(nearlyEqual(a.cross(b), 1.0f));
    std::cout << "cross(2D)     : PASS  " << a.cross(b) << "\n";

    // 방향 판별
    // b가 a의 왼쪽이면 양수
    assert(a.cross(b) > 0);
    std::cout << "방향 판별      : PASS  b는 a의 왼쪽\n";

    // sinAngle — 수직이면 1
    assert(nearlyEqual(a.sinAngle(b), 1.0f));
    std::cout << "sinAngle      : PASS  " << a.sinAngle(b) << "\n";

    // cosAngle — 수직이면 0
    assert(nearlyEqual(a.cosAngle(b), 0.0f));
    std::cout << "cosAngle      : PASS  " << a.cosAngle(b) << "\n";

    std::cout << "\n모든 Vector2 테스트 통과!\n";
}

int main() {
    testVector3();
    testVector2();

    return 0;
}