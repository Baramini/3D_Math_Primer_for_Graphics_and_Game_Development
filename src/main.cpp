#include <iostream>
#include <cassert>
#include "myMath.h"

void testCoordinateSpace() {
    std::cout << "=== CoordinateSpace Tests ===\n";

    // 1. worldSpace 기본 생성 확인
    assert(worldSpace.isOrthgonal());
    std::cout << "isOrthogonal(worldSpace) : PASS\n";

    // 2. localToWorld
    // origin이 (5, 0, 0)인 좌표계에서 local (1, 0, 0) → world (6, 0, 0)
    CoordinateSpace space(5.0f, 0.0f, 0.0f);
    Vector3<float> localPos(1.0f, 0.0f, 0.0f);
    Vector3<float> worldPos = space.localToWorld(localPos);
    assert(nearlyEqual(worldPos.x, 6.0f));
    assert(nearlyEqual(worldPos.y, 0.0f));
    assert(nearlyEqual(worldPos.z, 0.0f));
    std::cout << "localToWorld             : PASS  ";
    worldPos.print_components();

    // 3. worldToLocal
    // world (6, 0, 0) → local (1, 0, 0)
    Vector3<float> backToLocal = space.worldToLocal(worldPos);
    assert(nearlyEqual(backToLocal.x, 1.0f));
    assert(nearlyEqual(backToLocal.y, 0.0f));
    assert(nearlyEqual(backToLocal.z, 0.0f));
    std::cout << "worldToLocal             : PASS  ";
    backToLocal.print_components();

    // 4. localToWorld → worldToLocal 왕복 검증
    // 어떤 local 좌표든 변환 후 역변환하면 원래 값이 나와야 함
    Vector3<float> original(3.0f, 4.0f, 5.0f);
    Vector3<float> roundTrip = space.worldToLocal(space.localToWorld(original));
    assert(nearlyEqual(roundTrip.x, original.x));
    assert(nearlyEqual(roundTrip.y, original.y));
    assert(nearlyEqual(roundTrip.z, original.z));
    std::cout << "roundTrip                : PASS  ";
    roundTrip.print_components();

    // 5. isOrthogonal 실패 케이스
    // basis vector를 단위벡터가 아닌 값으로 오염시킴
    CoordinateSpace broken(0.0f, 0.0f, 0.0f);
    broken.right = Vector3<float>(2.0f, 0.0f, 0.0f);  // 길이가 2
    assert(!broken.isOrthgonal());
    std::cout << "isOrthogonal(broken)     : PASS\n";

    std::cout << "\n모든 CoordinateSpace 테스트 통과!\n";
}

int main() {
    testCoordinateSpace();
    return 0;
}