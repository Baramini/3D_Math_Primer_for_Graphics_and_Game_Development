// Vector2
template<typename T>
struct Vector2 {
    T x, y;

    Vector2(T x, T y) : x(x), y(y) {}
    void print_components() {
        std::cout << "( " << x << ", " << y << " )" << std::endl;
    }
};

template<typename X, typename Y>
Vector2(X, Y) -> Vector2<std::common_type_t<X, Y>>;