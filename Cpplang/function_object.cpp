#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <functional>

// Function Object
struct S {
    void operator()(int a, int b) {std::cout << "a + b = " << a + b << std::endl;}
    void operator()(char c) {std::cout << "Call func2: " << c << std::endl;}
};

int some_func1(const std::string& a) {
    std::cout << "Call func1: " << a << std::endl;
    return 0;
}

int main() {
    S some_obj;
    some_obj(3, 5);

    auto f = [](int a, int b) {std::cout << "a + b = " << a + b << std::endl;};
    f(3, 5);
    std::cout << std::endl;

    std::function<int(const std::string&)> f1 = some_func1;
    std::function<void(char)> f2 = S();
    std::function<void()> f3 = []() {std::cout << "Call func3: Yep" << std::endl;};

    f1("hello");
    f2('c');
    f3();
}