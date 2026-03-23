# 3D Game Math Library

> 📖 Based on *3D Math Primer for Graphics and Game Development* (2nd Edition)

A learning project implementing core game math concepts directly in C++.  
Beyond simple code writing, the goal is to understand how each mathematical concept is actually utilized within a game engine.

---

## 📌 Goals

- Hands-on implementation of core game math concepts (vectors, matrices, quaternions, etc.)
- Development into actual game modules like camera systems and colliders
- Understanding the mathematical structure of Unreal Engine / Unity

---

## 🛠️ Tech Stack

| | |
|---|---|
| Language | C++17 |
| Build | CMake 4.0 |
| Compiler | MSVC 19 (x64) |
| Editor | VSCode |

---

## 📁 Project Structure

```
GameMath/
├── src/
│   ├── myMath.h          # Entry point for all math libraries
│   ├── mathUtils.h       # Utility functions (nearlyEqual, toRadians, etc.)
│   ├── vector2.h         # 2D vector
│   ├── vector3.h         # 3D vector
│   ├── vector4.h         # 4D vector (homogeneous coordinates)
│   ├── matrix4x4.h       # 4x4 transformation matrix
│   └── main.cpp
├── tests/
│   └── main.cpp          # Test code
└── CMakeLists.txt
```

---

## 📐 Implementations

### ✅ Vector2
| Function | Description |
|---|---|
| `operator + - * /` | Arithmetic operators |
| `operator-()` | Negation |
| `dot()` | Dot product |
| `cross()` | 2D cross product (scalar) |
| `length()` | Magnitude |
| `normalize()` | Unit vector |
| `cosAngle()` | Cosine of angle between vectors |
| `sinAngle()` | Sine of angle between vectors |
| `lerp()` | Linear interpolation |
| `lerpClamp()` | Linear interpolation clamped to [0, 1] |
| `distance()` | Distance between two positions |

### ✅ Vector3
| Function | Description |
|---|---|
| `operator + - * /` | Arithmetic operators |
| `operator-()` | Negation |
| `dot()` | Dot product |
| `cross()` | Cross product |
| `length()` | Magnitude |
| `normalize()` | Unit vector |
| `cosAngle()` | Cosine of angle between vectors |
| `sinAngle()` | Sine of angle between vectors |
| `lerp()` | Linear interpolation |
| `lerpClamp()` | Linear interpolation clamped to [0, 1] |
| `distance()` | Distance between two positions |

> `Vector3f`, `Vector3d` type aliases provided

### ✅ Vector4
| Function | Description |
|---|---|
| `operator + - * /` | Arithmetic operators |
| `operator-()` | Negation |
| `operator*(Matrix4x4)` | Vector-matrix multiplication (row vector) |
| `dot()` | Dot product |
| `perspectiveDivide()` | Perspective divide (clip space → NDC) |
| `xyz()` | Extract xyz components as Vector3 |

> `Vector4f`, `Vector4d` type aliases provided

### ✅ Matrix4x4

> Row vector convention — transformations applied as `v * M`

**Construction**
| Function | Description |
|---|---|
| `identity()` | Identity matrix |
| `zero()` | Zero matrix |

**Operators**
| Function | Description |
|---|---|
| `operator+(Matrix4x4)` | Matrix addition |
| `operator*(float)` | Scalar multiplication |
| `operator*(Matrix4x4)` | Matrix multiplication |

**Linear Transforms**
| Function | Description |
|---|---|
| `makeRotationX(angle)` | Rotation matrix around X axis |
| `makeRotationY(angle)` | Rotation matrix around Y axis |
| `makeRotationZ(angle)` | Rotation matrix around Z axis |
| `makeRotation(vec, angle)` | Rotation matrix around arbitrary axis (Rodrigues) |
| `makeScale(x, y, z)` | Scale matrix along cardinal axes |
| `makeScale(vec, k)` | Scale matrix along arbitrary axis |
| `makeOrthoProj(vec)` | Orthographic projection onto plane (equivalent to makeScale k=0) |
| `makeReflection(vec)` | Reflection about plane (equivalent to makeScale k=-1) |
| `makeShearingXY(x, y)` | Shear X and Y by Z |
| `makeShearingYZ(y, z)` | Shear Y and Z by X |
| `makeShearingXZ(x, z)` | Shear X and Z by Y |

**Pending Implementation**
| Function | Description |
|---|---|
| `transpose()` | Transpose matrix |
| `determinant()` | Determinant |
| `inverse()` | Inverse matrix |
| `makeTranslation(x, y, z)` | Translation matrix |

### ✅ CoordinateSpace
| Function | Description |
|---|---|
| `isOrthogonal()` | Validates that basis vectors are orthonormal |
| `localToWorld()` | Transforms a position from local space to world space |
| `worldToLocal()` | Transforms a position from world space to local space |

> `worldSpace` — Predefined world coordinate space at origin (0, 0, 0)

### 🔲 Coming Soon
- `Matrix4x4` — Full implementation (transpose, determinant, inverse, translation)
- `Quaternion` — Rotation representation
- `Camera` — View / Projection transformation (OpenGL integration)
- `Collider` — AABB, Sphere collision detection

---

## 🚀 Build & Run

```bash
# 1. Clone
git clone https://github.com/Baramini/3D_Math_Primer_for_Graphics_and_Game_Development.git
cd 3D_Math_Primer_for_Graphics_and_Game_Development

# 2. Configure
cmake -S . -B build

# 3. Build
cmake --build build

# 4. Run
./build/Debug/GameMath.exe
```

---

## 📚 Reference

- [3D Math Primer for Graphics and Game Development](https://gamemath.com/) — Fletcher Dunn, Ian Parberry