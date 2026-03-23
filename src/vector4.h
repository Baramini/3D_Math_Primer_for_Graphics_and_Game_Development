// Vector4.h
template<typename T>
struct Vector4 {
    T x, y, z, w;

    Vector4() : x((T)0), y((T)0), z((T)0), w((T)0) {}
    Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

    // operator overloading
    Vector4 operator-() const {
        return Vector4(-x, -y, -z, -w);
    }
    Vector4 operator+(const Vector4& vec) const {
        return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
    }
    Vector4 operator-(const Vector4& vec) const {
        return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
    }
    Vector4 operator*(T scalar) const {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    // vector function
    Vector4 zero() {
        return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    T dot(const Vector4& vec) const {
        return (x * vec.x + y * vec.y + z * vec.z + w * vec.w);
    }
    Vector3<T> perspectiveDivide() const {
        return Vector3<T>(x / w, y / w, z / w);
    }
    Vector3<T> xyz() const {
        return Vector3<T>(x, y, z);
    }

    // other function
    void print_components() {
        std::cout << "( " << x << ", " << y << ", " << z << ", " << w << " )" << std::endl;
    }
};

template<typename X, typename Y, typename Z, typename W>
Vector4(X, Y, Z, W) -> Vector4<std::common_type_t<X, Y, Z, W>>;

using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;