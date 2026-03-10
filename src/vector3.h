// Vector3
template<typename T>
struct Vector3 {
    T x, y, z;

    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
    void print_components() {
        std::cout << "( " << x << ", " << y << ", " << z << " )" << std::endl;
    }
};

template<typename X, typename Y, typename Z>
Vector3(X, Y, Z) -> Vector3<std::common_type_t<X, Y, Z>>;