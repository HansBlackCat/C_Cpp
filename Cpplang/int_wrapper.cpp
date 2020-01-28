#include <iostream>

class Int {
    int data;

    public:  
        Int(int data): data(data) {}
        Int(const Int& i): data(i.data) {}

        operator int() {return data;}
};

// ++, -- overloading
/*
 * ++c -> operator++(); => return self (changed)
 * c++ -> operator++(int); => return self (unchanged)
 * int x = 1; func(++x)=={func(2), x==2} 
 * int x = 1; func(x++)=={func(1), x==2}
 * 
 * ex)
 * A& operator++() {//..//; return *this;} ---> Fast
 * A& operator++(int) {A temp(A); //..//; return temp;} ---> Slow
 */

class Test {
    int x;
    public: 
        Test(int x): x(x) {}
        Test(const Test& t): x(t.x) {}

        Test& operator++() {
            x++;
            std::cout << "Prefix" << std::endl;
            return *this;
        }
        Test operator++(int) {
            Test temp(*this);
            x++;
            std::cout << "Postfix" << std::endl;
            return temp;
        }
        int get_x() const {return x;}
};
void func(const Test& t) {
  std::cout << "x : " << t.get_x() << std::endl;
}

int main() {
    Int x = 3;
    int a = x + 4;
    x = a * x + 4;

    std::cout << x << std::endl;
    std::cout<<std::endl;

    Test t(3);
    func(t++);
    func(++t);
    std::cout << "x: " << t.get_x() << std::endl;
    
}