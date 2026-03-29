#include <iostream>
#include <cassert>
#include "myMath.h"

void testMatrixOperations() {
    std::cout << "=== Transpose / Inverse / Orthogonalize Tests ===\n";

    const float PI = 3.14159265f;

    // --- Transpose ---
    Matrix4x4 mat(
        1, 2, 3, 4,
        5, 6, 7, 8,
        9,10,11,12,
        13,14,15,16
    );
    Matrix4x4 t = mat.transpose();

    // (i,j) -> (j,i)
    assert(nearlyEqual(t.m[0][1], mat.m[1][0]));
    assert(nearlyEqual(t.m[0][2], mat.m[2][0]));
    assert(nearlyEqual(t.m[1][3], mat.m[3][1]));
    std::cout << "transpose                    : PASS\n";

    // transpose twice -> original
    Matrix4x4 tt = mat.transpose().transpose();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            assert(nearlyEqual(tt.m[i][j], mat.m[i][j]));
    std::cout << "transpose twice              : PASS\n";

    // rotation: transpose == inverse (Orthogonal Matrix property)
    Matrix4x4 rx = Matrix4x4::makeRotationX(PI / 4.0f);
    Matrix4x4 rxT = rx.transpose();
    Matrix4x4 rxInv = rx.inverse();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            assert(nearlyEqual(rxT.m[i][j], rxInv.m[i][j]));
    std::cout << "rotation: transpose==inverse : PASS\n";

    // --- Inverse ---
    // M * M⁻¹ = I
    Matrix4x4 scale = Matrix4x4::makeScale(2.0f, 3.0f, 4.0f);
    Matrix4x4 scaleInv = scale.inverse();
    Matrix4x4 shouldBeI = scale * scaleInv;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            assert(nearlyEqual(shouldBeI.m[i][j], (i == j) ? 1.0f : 0.0f));
    std::cout << "scale: M * M⁻¹ = I           : PASS\n";

    // reflection: M * M⁻¹ = I
    Vector3f axis(0.0f, 1.0f, 0.0f);
    Matrix4x4 refl = Matrix4x4::makeReflection(axis);
    Matrix4x4 reflInv = refl.inverse();
    Matrix4x4 reflI = refl * reflInv;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            assert(nearlyEqual(reflI.m[i][j], (i == j) ? 1.0f : 0.0f));
    std::cout << "reflection: M * M⁻¹ = I      : PASS\n";

    // singular matrix -> return zero matrix
    Matrix4x4 proj = Matrix4x4::makeOrthoProj(axis);
    Matrix4x4 projInv = proj.inverse();
    bool isZero = true;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (!nearlyEqual(projInv.m[i][j], 0.0f)) { isZero = false; break; }
    assert(isZero);
    std::cout << "singular -> zero             : PASS\n";

    // (M⁻¹)⁻¹ = M
    Matrix4x4 ry = Matrix4x4::makeRotationY(PI / 3.0f);
    Matrix4x4 ryInvInv = ry.inverse().inverse();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            assert(nearlyEqual(ryInvInv.m[i][j], ry.m[i][j]));
    std::cout << "(M⁻¹)⁻¹ = M                  : PASS\n";

    // --- Orthogonalize ---
    // inject drift error into rotation matrix
    Matrix4x4 drifted = Matrix4x4::makeRotationZ(PI / 6.0f);
    drifted.m[0][0] += 0.1f;
    drifted.m[1][1] += 0.1f;

    Matrix4x4 ortho = drifted.orthogonalize();

    Vector3f r0(ortho.m[0][0], ortho.m[0][1], ortho.m[0][2]);
    Vector3f r1(ortho.m[1][0], ortho.m[1][1], ortho.m[1][2]);
    Vector3f r2(ortho.m[2][0], ortho.m[2][1], ortho.m[2][2]);

    // unit vector check
    assert(nearlyEqual(r0.length(), 1.0f));
    assert(nearlyEqual(r1.length(), 1.0f));
    assert(nearlyEqual(r2.length(), 1.0f));
    std::cout << "orthogonalize: unit vectors  : PASS\n";

    // perpendicular check
    assert(nearlyEqual(r0.dot(r1), 0.0f));
    assert(nearlyEqual(r0.dot(r2), 0.0f));
    assert(nearlyEqual(r1.dot(r2), 0.0f));
    std::cout << "orthogonalize: perpendicular : PASS\n";

    // translation row preserved
    assert(nearlyEqual(ortho.m[3][0], drifted.m[3][0]));
    assert(nearlyEqual(ortho.m[3][1], drifted.m[3][1]));
    assert(nearlyEqual(ortho.m[3][2], drifted.m[3][2]));
    assert(nearlyEqual(ortho.m[3][3], drifted.m[3][3]));
    std::cout << "orthogonalize: translation preserved : PASS\n";

    std::cout << "\nAll tests passed!\n";
}

int main() {
    testMatrixOperations();
    return 0;
}