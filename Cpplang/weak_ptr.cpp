#include <iostream>
#include <memory>
#include <string>
#include <vector>

class A {
    std::string s;
    std::weak_ptr<A> other;

    public:  
        A(const std::string& s): s(s) {std::cout << "Acquire Resource" << std::endl;}
        ~A() {std::cout << "Call Destructor" << std::endl;}

        std::string name() {return s;}

        void set_other(std::weak_ptr<A> o) {other = o;}
        void access_other() {
            // What is lock() -> change to shared pointer
            std::shared_ptr<A> o = other.lock();
            if (o) {
                std::cout << "Approch: " << o -> name() << std::endl;
            } else {
                std::cout << "LOL already elimed" << std::endl;
            }
        }
};

int main() {
    std::vector<std::shared_ptr<A>> vec;
    vec.push_back(std::make_shared<A>("Resource 1"));
    vec.push_back(std::make_shared<A>("Resource 2"));

    vec[0] -> set_other(vec[1]);
    vec[1] -> set_other(vec[0]);

    std::cout << "vec[0] ref count: " << vec[0].use_count() << std::endl;
    std::cout << "vec[1] ref count: " << vec[1].use_count() << std::endl;

    // Contact obj with 'weak_ptr' 
    vec[0] -> access_other();

    // Delete Last element
    vec.pop_back();
    // Can't Access
    vec[0] -> access_other(); 
}