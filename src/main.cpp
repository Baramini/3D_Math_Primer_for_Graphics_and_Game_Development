#include <iostream>
#include "myMath.h"

int main() {
    Vector2 v1(1, 5);
    Vector3 v2(2, 8, 2.5);

    v1.print_components();
    v2.print_components();
    std::cout << typeid(v2.x).name() << '\n' << typeid(v2.z).name();

    return 0;
}