#include <iostream>
#include "myMath.h"

int main() {
    Matrix4x4 mat1(
        -0.1495f, -0.1986f, -0.9685f, 0.0f,
        -0.8256f, 0.5640f, 0.0117f, 0.0f,
        -0.5439f, -0.8015f, 0.2484f, 0.0f,
        1.7928f, -5.3116f, 8.0151f, 1.0f
    );
    mat1.inverse().printComponents();

    Matrix4x4 mat2 = Matrix4x4::identity();
    mat2.translate(4.0f, 2.0f, 3.0f).printComponents();
    mat2.rotateX(20.0f).translate(4.0f, 2.0f, 3.0f).printComponents();
    mat2.translate(4.0f, 2.0f, 3.0f).rotateX(20.0f).printComponents();
    mat2.persp_proj(5.0f).printComponents();

    std::cout << PI << std::endl;

    return 0;
}