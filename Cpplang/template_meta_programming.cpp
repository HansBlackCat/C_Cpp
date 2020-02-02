#include <iostream>
#include <typeinfo>

template <typename T, unsigned int N>
class Array {
    T data[N];

    public:  
        Array(T (&arr)[N]) {
            for (int i = 0; i < N; i++) {
                data[i] = arr[i];
            }
        }

        T* get_array() {return data;}
        unsigned int size() {return N;}

        void print_all() {
            for (int i = 0; i < N-1; i++) {
                std::cout << data[i] << ", ";
            }
            std::cout << data[N-1] << std::endl;
            std::cout << std::endl;
        }
};

template <int N> 
struct Int {
    static const int num = N;
};
template <typename T, typename U> 
struct add {
    typedef Int<T::num + U::num> result;
};

template <int N> 
struct Factorial {
    static const int result = N * Factorial<N-1>::result;
};
template <> 
struct Factorial<1> {
    static const int result = 1;
};

template <int N, int M>  
struct GCD {
    static const int value = GCD<M, N%M>::value;
};
template <int N>
struct GCD<N, 0> {
    static const int value = N;
};
template <int N, int M>  
struct Ratio {
    typedef Ratio<N, M> type;
    static const int divd = N;
    static const int divs = M; 
};
template <typename Ratio1, typename Ratio2>
struct _Ratio_add {
    typedef Ratio<Ratio1::divd * Ratio2::divs + Ratio2::divd * Ratio1::divs, Ratio1::divs * Ratio2::divs> type;
};
// Don't need to type ::type
template <class Ratio1, class Ratio2>
struct Ratio_add: _Ratio_add<Ratio1, Ratio2>::type {};



int main() {
    int arr[3] = {1, 2, 3};
    Array<int, 3> arr_w(arr);
    arr_w.print_all();

    std::cout << (typeid(Array<int, 3>) == typeid(Array<int, 5>)) << std::endl;
    std::cout << std::endl;

    typedef Int<1> one;
    typedef Int<2> two;
    typedef add<one, two>::result three;
    std::cout << "Res: " << three::num << std::endl;

    typedef Int<10> Kay;
    typedef Int<7> Lucky;
    typedef add<Kay, Lucky>::result answ;
    std::cout << answ::num << std::endl;
    std::cout << std::endl;

    std::cout << Factorial<6>::result << std::endl;
    std::cout << std::endl;

    typedef GCD<36, 24> gcd_first;
    std::cout << gcd_first::value << std::endl;
    std::cout << std::endl;

    typedef Ratio<2, 3> rt1;
    typedef Ratio<3, 2> rt2;
    typedef _Ratio_add<rt1, rt2> rt3;
    typedef Ratio_add<rt1, rt2> rtr3;
    std::cout << rt3::type::divd << "/" << rt3::type::divs << std::endl;
    std::cout << rtr3::divd << "/" << rtr3::divs << std::endl;
}