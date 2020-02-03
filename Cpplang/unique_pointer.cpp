#include <iostream>
#include <memory>
#include <vector>

// Resource Acquisition Is Initialization

class A {
    int* data;

    public:  
        A() {
            std::cout << "Acquire Resource" << std::endl;
            data = new int[100];
        }
        A(int i) {
            std::cout << "Acquire Resource" << std::endl;
            data = new int[100];
            data[0] = i;
        }
        void some() {std::cout << "Act like normal pointer" << std::endl;}
        void do_something_with_pointer(int a) {
            std::cout << "Do something with pointer" << std::endl;
            data[0] = a;
        }
        ~A() {
            std::cout << "Delete Resource" << std::endl;
            delete[] data;
        }
};

// Delete function
class B {
    public:  
        B(int a) {std::cout << "B init" << std::endl;};
        B(const B& a) = delete;
};

// std::make_unique
class Foo {
    int a, b;

    public:  
        Foo(int _a, int _b): a(_a), b(_b) {std::cout << "Call Constructor" << std::endl;}
        void print() {std::cout << "a, b: " << a << ", " << b << std::endl;}
        ~Foo() {std::cout << "Call Destructor" << std::endl;}
};

void do_something() {
    // A* pa(new A());
    std::unique_ptr<A> upa(new A());
    // Can't copy, of cource
    // *call to implicitly-deleted copy constructor*
    // std::unique_ptr<A> upb = upa;
    upa -> some();

    std::unique_ptr<A> upb = std::move(upa);
    upb -> some();
    // use unassinged pointer *RUNTIME ERROR*
    // upa -> some();

    std::cout << "-- Origin unqptr loc: " << upa.get() << std::endl;
}
void i_want_to_have_unqptr(A* ptr) {ptr -> do_something_with_pointer(3);}

int main() {
    do_something();

    std::cout << "\n--- delete function ---" << std::endl;
    B b(3);
    // *call to implicitly-deleted copy constructor*
    // B b_prime(b);

    std::cout << "\n--- unqptr in function ---" << std::endl;
    std::unique_ptr<A> upa(new A());
    // .get method return *REAL* obj address
    i_want_to_have_unqptr(upa.get());

    std::cout << "\n--- std::make_unique ---" << std::endl;
    auto ptr = std::make_unique<Foo>(3, 5);
    ptr -> print();

    std::cout << "\n--- STL container ---" << std::endl;
    std::vector<std::unique_ptr<A>> vec;
    std::unique_ptr<A> pa(new A(1));
    
    vec.push_back(std::move(pa));
    vec.emplace_back(new A(1));
    vec.back() -> some();
    

    std::cout << "--& PROCESS_END &--" << std::endl;
}