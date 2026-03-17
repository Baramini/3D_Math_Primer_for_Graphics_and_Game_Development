#include <iostream>
#include <cassert>
#include "myMath.h"

void testMatrix4x4() {
    std::cout << "=== Matrix4x4 Tests ===\n";

    // 1. 단위행렬 생성
    Matrix4x4 identity = Matrix4x4::identity();
    assert(nearlyEqual(identity.m[0][0], 1.0f));
    assert(nearlyEqual(identity.m[1][1], 1.0f));
    assert(nearlyEqual(identity.m[2][2], 1.0f));
    assert(nearlyEqual(identity.m[3][3], 1.0f));
    assert(nearlyEqual(identity.m[0][1], 0.0f));
    std::cout << "identity         : PASS\n";

    // 2. 영행렬 생성
    Matrix4x4 zero = Matrix4x4::zero();
    assert(nearlyEqual(zero.m[0][0], 0.0f));
    assert(nearlyEqual(zero.m[3][3], 0.0f));
    std::cout << "zero             : PASS\n";

    // 3. operator+ (행렬 덧셈)
    Matrix4x4 a(
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    );
    Matrix4x4 b(
        2,0,0,0,
        0,2,0,0,
        0,0,2,0,
        0,0,0,2
    );
    Matrix4x4 add = a + b;
    assert(nearlyEqual(add.m[0][0], 3.0f));
    assert(nearlyEqual(add.m[1][1], 3.0f));
    assert(nearlyEqual(add.m[2][2], 3.0f));
    assert(nearlyEqual(add.m[3][3], 3.0f));
    std::cout << "operator+        : PASS\n";

    // 4. operator* scalar
    Matrix4x4 scaled = a * 3.0f;
    assert(nearlyEqual(scaled.m[0][0], 3.0f));
    assert(nearlyEqual(scaled.m[1][1], 3.0f));
    std::cout << "operator*(scalar): PASS\n";

    // 5. operator* Matrix (행렬 곱)
    // 단위행렬 * 단위행렬 = 단위행렬
    Matrix4x4 mul = a * identity;
    assert(nearlyEqual(mul.m[0][0], 1.0f));
    assert(nearlyEqual(mul.m[1][1], 1.0f));
    assert(nearlyEqual(mul.m[2][2], 1.0f));
    assert(nearlyEqual(mul.m[3][3], 1.0f));
    std::cout << "operator*(mat)   : PASS\n";

    // 6. vec * mat (row vector 기준)
    // 단위행렬 곱하면 벡터 그대로
    Vector4f vec(1.0f, 2.0f, 3.0f, 1.0f);
    Vector4f result = vec * identity;
    assert(nearlyEqual(result.x, 1.0f));
    assert(nearlyEqual(result.y, 2.0f));
    assert(nearlyEqual(result.z, 3.0f));
    assert(nearlyEqual(result.w, 1.0f));
    std::cout << "vec * identity   : PASS  ";
    result.print_components();

    // 7. 변환 행렬 곱 순서 검증 (row vector 기준)
    // v * M_a * M_b 순서로 적용되는지 확인
    Matrix4x4 ma(
        2,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    );
    Matrix4x4 mb(
        1,0,0,0,
        0,3,0,0,
        0,0,1,0,
        0,0,0,1
    );
    // v * (ma * mb) == (v * ma) * mb
    Vector4f v(1.0f, 1.0f, 1.0f, 1.0f);
    Vector4f r1 = v * (ma * mb);
    Vector4f r2 = (v * ma) * mb;
    assert(nearlyEqual(r1.x, r2.x));
    assert(nearlyEqual(r1.y, r2.y));
    assert(nearlyEqual(r1.z, r2.z));
    assert(nearlyEqual(r1.w, r2.w));
    std::cout << "결합법칙 검증     : PASS  ";
    r1.print_components();

    std::cout << "\n모든 Matrix4x4 테스트 통과!\n";
}

int main() {
    testMatrix4x4();
    return 0;
}