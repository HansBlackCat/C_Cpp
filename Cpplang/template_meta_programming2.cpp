#include <iostream>
#include <typeinfo>

/*
bool is_prime(int n) {
    if (n==2) return true;
    if (n==3) return true;
    for (int i = 2; i <= n/2; i++) {
        if (n%i==0) return false;
    }
    return true;
}
*/

template<int N> 
struct INT {
    static const int num = N;
};
template<typename a, typename b>
struct ADD {
    using result = INT<a::num + b::num>;
};
template<typename a, typename b>
struct DIV {
    using result = INT<a::num / b::num>;
};

using one = INT<1>;
using two = INT<2>;
using three = INT<3>;

template <typename N, typename M> 
struct check_div {
    static const bool result = 
        (N::num % M::num==0) || check_div<N, typename ADD<N, one>::result>::result;
};
template <typename N> 
struct check_div<N, typename DIV<N, two>::result> {
    static const bool result = (N::num%(N::num/2))==0;
};

template<typename N> 
struct _is_prime {
    static const bool result = !check_div<N, two>::result;
};
template<> 
struct _is_prime<two> {
    static const bool result = true;
};
template<> 
struct _is_prime<three> {
    static const bool result = true;
};
template<int n> 
struct is_prime {
    static const bool result = _is_prime<INT<n>>::result;
};

// UNIT CALCU
template <typename U, typename V, typename W>
struct Dim {
    using M = U;
    using L = V;
    using T = W;

    using type = Dim<M, L, T>;
}

int main() {
    std::cout << "Prime Calculating(61): " << is_prime<61>::result << std::endl;
}
