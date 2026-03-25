#include <iostream>
#include <cassert>
#include "myMath.h"

void testDeterminant() {
    std::cout << "=== Determinant Tests ===\n";

    // 1. identity matrix — det = 1
    Matrix4x4 identity = Matrix4x4::identity();
    assert(nearlyEqual(identity.determinant(), 1.0f));
    std::cout << "identity det         : PASS  " << identity.determinant() << "\n";

    // 2. zero matrix — det = 0
    Matrix4x4 zero = Matrix4x4::zero();
    assert(nearlyEqual(zero.determinant(), 0.0f));
    std::cout << "zero det             : PASS  " << zero.determinant() << "\n";

    // 3. rotation — det = 1
    const float PI = 3.14159265f;
    Matrix4x4 rx = Matrix4x4::makeRotationX(PI / 4.0f);
    Matrix4x4 ry = Matrix4x4::makeRotationY(PI / 3.0f);
    Matrix4x4 rz = Matrix4x4::makeRotationZ(PI / 6.0f);
    assert(nearlyEqual(rx.determinant(), 1.0f));
    assert(nearlyEqual(ry.determinant(), 1.0f));
    assert(nearlyEqual(rz.determinant(), 1.0f));
    std::cout << "rotation det         : PASS  "
              << rx.determinant() << " "
              << ry.determinant() << " "
              << rz.determinant() << "\n";

    // 4. scale — det = x * y * z
    Matrix4x4 scale = Matrix4x4::makeScale(2.0f, 3.0f, 4.0f);
    assert(nearlyEqual(scale.determinant(), 24.0f));
    std::cout << "scale det            : PASS  " << scale.determinant() << "\n";

    // 5. uniform scale k=2 — det = k³ = 8
    Matrix4x4 uscale = Matrix4x4::makeScale(2.0f, 2.0f, 2.0f);
    assert(nearlyEqual(uscale.determinant(), 8.0f));
    std::cout << "uniform scale det    : PASS  " << uscale.determinant() << "\n";

    // 6. reflection — det = -1
    Vector3f axis(0.0f, 1.0f, 0.0f);
    Matrix4x4 refl = Matrix4x4::makeReflection(axis);
    assert(nearlyEqual(refl.determinant(), -1.0f));
    std::cout << "reflection det       : PASS  " << refl.determinant() << "\n";

    // 7. shearing — det = 1
    Matrix4x4 shear = Matrix4x4::makeSheeringXY(2.0f, 3.0f);
    assert(nearlyEqual(shear.determinant(), 1.0f));
    std::cout << "shearing det         : PASS  " << shear.determinant() << "\n";

    // 8. ortho projection — det = 0 (singular)
    Matrix4x4 proj = Matrix4x4::makeOrthoProj(axis);
    assert(nearlyEqual(proj.determinant(), 0.0f));
    std::cout << "ortho proj det       : PASS  " << proj.determinant() << "\n";

    // 9. arbitrary scale k=3 — det = k = 3
    Matrix4x4 arbScale = Matrix4x4::makeScale(axis, 3.0f);
    assert(nearlyEqual(arbScale.determinant(), 3.0f));
    std::cout << "arbitrary scale det  : PASS  " << arbScale.determinant() << "\n";

    // 10. det(A * B) = det(A) * det(B)
    float detA = rx.determinant();
    float detB = scale.determinant();
    float detAB = (rx * scale).determinant();
    assert(nearlyEqual(detAB, detA * detB));
    std::cout << "det(A*B)=det(A)*det(B): PASS  " << detAB << " == " << detA * detB << "\n";

    std::cout << "\n모든 Determinant 테스트 통과!\n";
}

int main() {
    testDeterminant();
    return 0;
}