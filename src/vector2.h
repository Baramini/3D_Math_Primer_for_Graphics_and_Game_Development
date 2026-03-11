// Vector2
template<typename T>
struct Vector2 {
    T x, y;

    Vector2(T x, T y) : x(x), y(y) {}

    // operator overloading
    Vector2 operator-() const {
        return Vector2(-x, -y);
    }
    Vector2 operator+(const Vector2& vec) const {
        return Vector2(x + vec.x, y + vec.y);
    }
    Vector2 operator-(const Vector2& vec) const {
        return Vector2(x - vec.x, y - vec.y);
    }
    Vector2 operator*(T scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    // vector function
    Vector2 zero() {
        return Vector2(0, 0);
    }
    T dot(const Vector2& vec) const {
        return (x * vec.x + y * vec.y);
    }
    auto cross(const Vector2& vec) const {
        return x * vec.y - vec.x * y;
    }
    auto length() const {
        return sqrt(x * x + y * y);
    }
    auto cosAngle(const Vector2& vec) const {
        return dot(vec) / (length() * vec.length());
    }
    auto sinAngle(const Vector2& vec) const {
        return cross(vec) / (length() * vec.length());
    }
    Vector2 normalize() const {
        T magnitude = length();
        if (magnitude == 0) return Vector2(0, 0);
        return Vector2(x / magnitude, y / magnitude);
    }
    Vector2 lerp(const Vector2& vec, float t) const {
        return *this + (vec - *this) * t;
    }
    Vector2 lerpClamp(const Vector2& vec, float t) const {
        t = t < 0.0f ? 0.0f : t;
        t = t > 1.0f ? 1.0f : t;
        return *this + (vec - *this) * t;
    }
    auto distance(const Vector2& vec) const {
        return (*this - vec).length();
    }

    // other function
    void print_components() {
        std::cout << "( " << x << ", " << y << " )" << std::endl;
    }
};

template<typename X, typename Y>
Vector2(X, Y) -> Vector2<std::common_type_t<X, Y>>;