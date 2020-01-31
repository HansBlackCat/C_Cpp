#include <iostream>

class Base {
    public:  
        Base() {std::cout<<"Called Base Constructor"<<std::endl;}
        virtual ~Base() {std::cout<<"Called Base Destructor"<<std::endl;}
};
class Derived: public Base {
    public:  
        Derived() {std::cout<<"Called Derived Constructor"<<std::endl;}
        ~Derived() {std::cout<<"Called Derived Destructor"<<std::endl;}
};

class A {
    public:  
        virtual void show() {std::cout<<"class A"<<std::endl;}
};
class B: public A {
    public:  
        void show() override {std::cout<<"class B"<<std::endl;}
};
void test(A& a) {a.show();}

class Parent {
    public:  
        virtual void func1();
        virtual void func2();
};
class Child: public Parent {
    public:  
        virtual void func1();
        void func3();
};

class Animal {
    public:  
        Animal() {}
        virtual ~Animal() {}
        virtual void speak() = 0;
};
class Dog: public Animal {
    public:  
        Dog(): Animal() {}
        void speak() override {std::cout<<"Bark Bark"<<std::endl;}
};
class Cat: public Animal {
    public:  
        public:  
            Cat(): Animal() {}
            void speak() override {std::cout<<"Nyah Nyah"<<std::endl;}
};

class Base1 {
    public:  
        int a;
};
class Base2 {
    public:  
        int b;
};
class Derive_Multi: public Base1, public Base2 {
    public:  
        int c;
};

int main() {
    {Derived d;}
    std::cout<<std::endl;
    {
        Base* p = new Derived();
        delete p;
    }
    std::cout<<std::endl;

    A a; B b;
    test(a);
    test(b);
    std::cout<<std::endl;

    Animal* dog = new Dog();
    Animal* cat = new Cat();
    
    dog -> speak();
    cat -> speak();
}
