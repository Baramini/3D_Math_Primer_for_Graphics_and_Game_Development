// Vector3
template<typename T>
struct Vector3 {
    T x, y, z;

    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

    // operator overloading
    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }
    Vector3 operator+(const Vector3& vec) const {
        return Vector3(x + vec.x, y + vec.y, z + vec.z);
    }
    Vector3 operator-(const Vector3& vec) const {
        return Vector3(x - vec.x, y - vec.y, z - vec.z);
    }
    Vector3 operator*(T scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // vector function
    Vector3 zero() {
        return Vector3(0, 0, 0);
    }
    T dot(const Vector3& vec) const {
        return (x * vec.x + y * vec.y + z * vec.z);
    }
    Vector3 cross(const Vector3& vec) const {
        return Vector3(y * vec.z - vec.y * z, z * vec.x - vec.z * x, x * vec.y - vec.x * y);
    }
    auto length() const {
        return sqrt(x * x + y * y + z * z);
    }
    auto cosAngle(const Vector3& vec) const {
        return dot(vec) / (length() * vec.length());
    }
    auto sinAngle(const Vector3& vec) const {
        return cross(vec).length() / (length() * vec.length());
    }
    Vector3 normalize() const {
        T magnitude = length();
        if (magnitude == 0) return Vector3(0, 0, 0);
        return Vector3(x / magnitude, y / magnitude, z / magnitude);
    }
    Vector3 lerp(const Vector3& vec, float t) const {
        return *this + (vec - *this) * t;
    }
    Vector3 lerpClamp(const Vector3& vec, float t) const {
        t = t < 0.0f ? 0.0f : t;
        t = t > 1.0f ? 1.0f : t;
        return *this + (vec - *this) * t;
    }
    auto distance(const Vector3& vec) const {
        return (*this - vec).length();
    }

    // other function
    void print_components() {
        std::cout << "( " << x << ", " << y << ", " << z << " )" << std::endl;
    }
};

template<typename X, typename Y, typename Z>
Vector3(X, Y, Z) -> Vector3<std::common_type_t<X, Y, Z>>;