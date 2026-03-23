#include <iostream>
#include <cassert>
#include "myMath.h"

void drawLine2D(char grid[][40], int WIDTH, int HEIGHT, float SCALE,
                float x0, float y0, float x1, float y1, char ch = '#') {
    // Bresenham's line algorithm
    int px0 = (int)(x0 * SCALE + WIDTH  / 2);
    int py0 = (int)(-y0 * SCALE + HEIGHT / 2);
    int px1 = (int)(x1 * SCALE + WIDTH  / 2);
    int py1 = (int)(-y1 * SCALE + HEIGHT / 2);

    int dx = abs(px1 - px0);
    int dy = abs(py1 - py0);
    int sx = px0 < px1 ? 1 : -1;
    int sy = py0 < py1 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (px0 >= 0 && px0 < WIDTH && py0 >= 0 && py0 < HEIGHT)
            grid[py0][px0] = ch;
        if (px0 == px1 && py0 == py1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; px0 += sx; }
        if (e2 <  dx) { err += dx; py0 += sy; }
    }
}

void visualize2D(const char* label, Vector4f points[], int count, float SCALE = 3.0f) {
    const int WIDTH  = 40;
    const int HEIGHT = 20;

    char grid[20][40];
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            grid[y][x] = '.';

    // draw edges (connect points in order, close the loop)
    for (int i = 0; i < count; i++) {
        int next = (i + 1) % count;
        drawLine2D(grid, WIDTH, HEIGHT, SCALE,
            points[i].x, points[i].y,
            points[next].x, points[next].y);
    }

    // draw corners
    for (int i = 0; i < count; i++) {
        int px = (int)(points[i].x * SCALE + WIDTH  / 2);
        int py = (int)(-points[i].y * SCALE + HEIGHT / 2);
        if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
            grid[py][px] = '@';
    }

    // draw axes
    for (int x = 0; x < WIDTH;  x++) grid[HEIGHT / 2][x] = '-';
    for (int y = 0; y < HEIGHT; y++) grid[y][WIDTH  / 2] = '|';
    grid[HEIGHT / 2][WIDTH / 2] = '+';

    std::cout << "\n[" << label << "]\n";
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++)
            std::cout << grid[y][x];
        std::cout << "\n";
    }
}

void testTransformVisual() {
    std::cout << "=== Transform Visual Tests ===\n";

    const float PI = 3.14159265f;

    Vector4f square[4] = {
        Vector4f( 1.0f,  1.0f, 0.0f, 1.0f),
        Vector4f(-1.0f,  1.0f, 0.0f, 1.0f),
        Vector4f(-1.0f, -1.0f, 0.0f, 1.0f),
        Vector4f( 1.0f, -1.0f, 0.0f, 1.0f)
    };

    visualize2D("Original", square, 4);

    // --- Projection ---
    // project onto XY plane (n = Z axis)
    Vector3f zAxis(0.0f, 0.0f, 1.0f);
    Matrix4x4 proj = Matrix4x4::makeOrthoProj(zAxis);
    Vector4f proj_pts[4];
    for (int i = 0; i < 4; i++) proj_pts[i] = square[i] * proj;
    visualize2D("OrthoProj onto XY (n=Z)", proj_pts, 4);

    // project onto plane perpendicular to (1,1,0)
    Vector3f diagAxis(1.0f, 1.0f, 0.0f);
    Matrix4x4 proj2 = Matrix4x4::makeOrthoProj(diagAxis);
    Vector4f proj2_pts[4];
    for (int i = 0; i < 4; i++) proj2_pts[i] = square[i] * proj2;
    visualize2D("OrthoProj (1,1,0)", proj2_pts, 4);

    // --- Reflection ---
    // reflect about YZ plane (n = X axis)
    Vector3f xAxis(1.0f, 0.0f, 0.0f);
    Matrix4x4 refl = Matrix4x4::makeReflection(xAxis);
    Vector4f refl_pts[4];
    for (int i = 0; i < 4; i++) refl_pts[i] = square[i] * refl;
    visualize2D("Reflection about YZ (n=X)", refl_pts, 4);

    // reflect about plane perpendicular to (1,1,0)
    Matrix4x4 refl2 = Matrix4x4::makeReflection(diagAxis);
    Vector4f refl2_pts[4];
    for (int i = 0; i < 4; i++) refl2_pts[i] = square[i] * refl2;
    visualize2D("Reflection (1,1,0)", refl2_pts, 4);

    // --- Shearing ---
    // shear XY — Z값에 따라 X,Y가 밀림
    // 현재 square는 Z=0이라 효과 없음 → Z값 있는 점으로 테스트
    Vector4f cube[4] = {
        Vector4f( 1.0f,  1.0f, 1.0f, 1.0f),
        Vector4f(-1.0f,  1.0f, 1.0f, 1.0f),
        Vector4f(-1.0f, -1.0f, 1.0f, 1.0f),
        Vector4f( 1.0f, -1.0f, 1.0f, 1.0f)
    };

    Matrix4x4 shXY = Matrix4x4::makeSheeringXY(0.5f, 0.5f);
    Vector4f shXY_pts[4];
    for (int i = 0; i < 4; i++) shXY_pts[i] = cube[i] * shXY;
    visualize2D("ShearXY (s=0.5, z=1)", shXY_pts, 4);

    // shear YZ — X값에 따라 Y,Z가 밀림
    Matrix4x4 shYZ = Matrix4x4::makeSheeringYZ(0.5f, 0.5f);
    Vector4f shYZ_pts[4];
    for (int i = 0; i < 4; i++) shYZ_pts[i] = square[i] * shYZ;
    visualize2D("ShearYZ (s=0.5)", shYZ_pts, 4);

    // shear XZ — Y값에 따라 X,Z가 밀림
    Matrix4x4 shXZ = Matrix4x4::makeSheeringXZ(0.5f, 0.5f);
    Vector4f shXZ_pts[4];
    for (int i = 0; i < 4; i++) shXZ_pts[i] = square[i] * shXZ;
    visualize2D("ShearXZ (s=0.5)", shXZ_pts, 4);

    // --- makeScale(k=0) vs makeOrthoProj 비교 ---
    // 둘이 같은 결과여야 함
    Matrix4x4 scaleProj = Matrix4x4::makeScale(diagAxis, 0.0f);
    Matrix4x4 orthoProj = Matrix4x4::makeOrthoProj(diagAxis);
    Vector4f sp_pts[4], op_pts[4];
    for (int i = 0; i < 4; i++) {
        sp_pts[i] = square[i] * scaleProj;
        op_pts[i] = square[i] * orthoProj;
    }
    bool projEqual = true;
    for (int i = 0; i < 4; i++) {
        if (!nearlyEqual(sp_pts[i].x, op_pts[i].x) ||
            !nearlyEqual(sp_pts[i].y, op_pts[i].y)) {
            projEqual = false;
            break;
        }
    }
    std::cout << "\nmakeScale(k=0) == makeOrthoProj : " << (projEqual ? "PASS" : "FAIL") << "\n";

    // --- makeScale(k=-1) vs makeReflection 비교 ---
    Matrix4x4 scaleRefl = Matrix4x4::makeScale(diagAxis, -1.0f);
    Matrix4x4 reflMat   = Matrix4x4::makeReflection(diagAxis);
    Vector4f sr_pts[4], rm_pts[4];
    for (int i = 0; i < 4; i++) {
        sr_pts[i] = square[i] * scaleRefl;
        rm_pts[i] = square[i] * reflMat;
    }
    bool reflEqual = true;
    for (int i = 0; i < 4; i++) {
        if (!nearlyEqual(sr_pts[i].x, rm_pts[i].x) ||
            !nearlyEqual(sr_pts[i].y, rm_pts[i].y)) {
            reflEqual = false;
            break;
        }
    }
    std::cout << "makeScale(k=-1) == makeReflection : " << (reflEqual ? "PASS" : "FAIL") << "\n";
}

int main() {
    testTransformVisual();
    return 0;
}