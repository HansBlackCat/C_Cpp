#include <iostream>

struct A {
    double d;
    int f();
    static int g();
};

struct B {
    B(int x) {}
    int f() {return 0;}
};

struct A {
    int f() {return 0;}
};

int main() {
    int a = 3;
    decltype(a) b = 2; // int

    int& r_a = a;
    decltype(r_a) r_b = b; // int&

    int&& x = 3;
    decltype(x) y = 2; // int&&

    A* aa;
    decltype(aa -> d) dd = 0.1; //double

    int a2, b2;
    decltype(a2 + b2) c; //prvalue(int)

    int a3;
    decltype((a3)) c3 = a; //lvalue(int&)

    decltype(A().f()) ret_val;

    decltype(B().f()) ret_val2;
}