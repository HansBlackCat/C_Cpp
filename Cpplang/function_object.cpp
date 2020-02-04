#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <algorithm>

using std::vector;

// Function Object
struct S {
    void operator()(int a, int b) {std::cout << "a + b = " << a + b << std::endl;}
    void operator()(char c) {std::cout << "Call func2: " << c << std::endl;}
};

struct Ref_get_func {
    int data;
    Ref_get_func(int data): data(data) {std::cout << "Call normal Initializer!" << std::endl;}
    Ref_get_func(const Ref_get_func& s) {
        std::cout << "Call copy Initializer!" << std::endl;
        data = s.data;
    }
    Ref_get_func(Ref_get_func&& s) {
        std::cout << "Call move Initializer!" << std::endl;
        data = s.data;
    }
};
void do_something(Ref_get_func& s1, const Ref_get_func& s2) {
    s1.data = s2.data + 3;
}

class Function_in_Class {
    int c;

    public:
        Function_in_Class(int c): c(c) {}
        void some_func() {std::cout << "Inner Data: " << c << std::endl;}
        int plus_func() {
            std::cout << "++: " << ++c << std::endl;
            return c;
        }
        int const_func() const {
            std::cout << "Consty~: " << c << std::endl;
            return c;
        }
        static void static_and_void() {}
};

int some_func1(const std::string& a) {
    std::cout << "Call func1: " << a << std::endl;
    return 0;
}

void add(int x, int y) {
    std::cout << x << " + " << y << " = " << x+y << std::endl;
}
void substract(int x, int y) {
    std::cout << x << " - " << y << " = " << x-y << std::endl;
}

int main() {
    S some_obj;
    some_obj(3, 5);

    auto f = [](int a, int b) {std::cout << "a + b = " << a + b << std::endl;};
    f(3, 5);
    std::cout << std::endl;
    // ------------------------------------------------

    std::function<int(const std::string&)> f1 = some_func1;
    std::function<void(char)> f2 = S();
    std::function<void()> f3 = []() {std::cout << "Call func3: Yep" << std::endl;};

    f1("hello");
    f2('c');
    f3();
    std::cout << std::endl;

    Function_in_Class a(5);
    // Have to Specify 'Self' 
    std::function<void(Function_in_Class&)> some_f = &Function_in_Class::some_func;
    std::function<int(const Function_in_Class&)> const_f = &Function_in_Class::const_func;
    std::function<int(Function_in_Class&)> add_f = &Function_in_Class::plus_func;

    some_f(a);
    const_f(a);
    add_f(a);
    std::cout << std::endl;
    // ------------------------------------------------

    vector<int> v(1);
    vector<int> w(2);
    vector<int> x(3);
    vector<int> y(4);

    vector<vector<int>> container;
    container.push_back(w);
    container.push_back(y);
    container.push_back(v);
    container.push_back(x);

    // If member func, need to use std::function for size_t
    std::function<size_t(const vector<int>&)> sz_func = &vector<int>::size;

    vector<int> size_vec(4);
    // It's also work
    // std::transform(container.begin(), container.end(), size_vec.begin(), std::mem_fn(&vector<int>::size));
    // std::transform(container.begin(), container.end(), size_vec.begin(), [](const auto& v){return v.size});
    std::transform(container.begin(), container.end(), size_vec.begin(), sz_func);
    for (auto itr = size_vec.begin(); itr != size_vec.end(); itr++) {
        std::cout << "Size of Vector: " << *itr << std::endl;
    }
    std::cout << std::endl;
    // ------------------------------------------------

    auto add_with_2 = std::bind(add, 2, std::placeholders::_1);
    add_with_2(3);
    // Second parameter ignored
    add_with_2(3, 4);
    add_with_2(3, 5, 6, 12);    

    auto subtract_from_2 = std::bind(substract, std::placeholders::_1, 2);
    auto negate = std::bind(substract, std::placeholders::_2, std::placeholders::_1);

    subtract_from_2(3);
    negate(4, 2);
    std::cout << std::endl;
    // ------------------------------------------------

    Ref_get_func s1(1), s2(2);
    std::cout << "Before: " << s1.data << std::endl;
    
    // Need std::ref to Implicit-Move
    // cf) constref -> std::cref
    auto do_something_with_s1 = std::bind(do_something, std::ref(s1), std::placeholders::_1);
    do_something_with_s1(s2);
    std::cout << "After: " << s1.data << std::endl;

}