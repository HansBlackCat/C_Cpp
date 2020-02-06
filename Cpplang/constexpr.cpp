#include <iostream>
#include <type_traits>

template <int N> 
struct A {
    int operator()() {return N;}
};

int factorial(int N) {
    int tot = 1;
    for (int i = 1; i <= N; i++) {
        tot *= i;
    }
    return tot;
}

template <int N> 
struct Factorial {
    static const int value = N * Factorial<N-1>::value;
};
template <> 
struct Factorial<0> {
    static const int value = 1;
};

template <int N> 
struct Fac {
    int operator()() {return N;}
};

constexpr int factorial_constexpr(int N) {
    int tot = 1;
    for (int i = 1; i <= N; i++) {
        tot *= i;
    }
    return tot;
}


class Vect {
    int _x, _y;

    public: 
        constexpr Vect(int _x, int _y): _x(_x), _y(_y) {};

        constexpr int x() const {return _x;}
        constexpr int y() const {return _y;} 
};
constexpr Vect AddVec(const Vect& v1, const Vect& v2) {
    return {v1.x() + v2.x(), v1.y() + v2.y()};
}


template <typename T> 
void show_value(T t) {
    std::cout << "Not pointer: " << t << std::endl;
}
template <typename T>  
void show_value(T* t) {
    std::cout << "Pointer: " << *t << std::endl;
}
/*
template <typename T>  
void show_value(T& t) {
    std::cout << "Ref: " << t << std::endl;
}
*/

template <typename T>  
void show_value_upgrade(T t) {
    if constexpr (std::is_pointer<T>::value) {
        std::cout << "Is pointer: " << *t << std::endl;
    } else {
        std::cout << "Is not pointer: " << t << std::endl;
    }
}


int main() {
    constexpr int size = 3;
    int arr[size];

    constexpr int N = 10;
    A<N> a;
    std::cout << a() << std::endl;

    constexpr int number = 3;
    enum B { x = number, y, z};
    std::cout << B::x << std::endl;

    const auto sizee = 4;
    int arrr[sizee];
    std::cout << std::endl;

    // Fac<factorial(5)> fac_a;
    Fac<Factorial<10>::value> fac_a;
    std::cout << fac_a() << std::endl;

    Fac<factorial_constexpr(10)> fac_b;
    std::cout << fac_b() << "\n" << std::endl;

    constexpr Vect v1{1, 2};
    constexpr Vect v2{2, 3};

    A<v1.x()> v1a;
    std::cout << v1a() << std::endl;

    A<AddVec(v1, v2).x()> v2ad;
    std::cout << v2ad() << "\n" << std::endl; 

    int show_x = 3;
    int* pointer_x = &show_x;
    int& ref_x = show_x;

    show_value(show_x);
    show_value(pointer_x);
    show_value(ref_x);

    show_value_upgrade(show_x);
    show_value_upgrade(pointer_x);
    show_value_upgrade(ref_x);
}