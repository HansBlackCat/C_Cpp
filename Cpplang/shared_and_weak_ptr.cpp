#include <iostream>
#include <string>
#include <vector>
#include <memory>

// self direct share_ptr
// Inherit std::enable_shared_from_this<A>
class A: public std::enable_shared_from_this<A> {
    int* data;

    public:  
        A() {
            data = new int[100];
            std::cout << "Acquire Resource" << std::endl;
        }
        ~A() {
            std::cout << "Call Destructor" << std::endl;
            delete[] data;
        }
        // method from std::enable_shared_from_this 
        std::shared_ptr<A> get_shared_ptr() {return shared_from_this();}
};

class self_direct_shareptr {
    int* data;
    
    public:  
        self_direct_shareptr() {
            data = new int[100];
            std::cout << "Acquire Resource" << std::endl;
        }
        ~self_direct_shareptr() {
            std::cout << "Call Destructor" << std::endl;
            delete[] data;
        }
};

int main() {
    std::vector<std::shared_ptr<A>> vec;

    vec.push_back(std::shared_ptr<A>(new A()));
    vec.push_back(std::shared_ptr<A>(vec[0]));
    vec.push_back(std::shared_ptr<A>(vec[1]));

    std::cout << "Eliminate First(Ref counter 3->2)" << std::endl;
    vec.erase(vec.begin());

    std::cout << "Eliminate Second(Ref counter 2->1)" << std::endl;
    vec.erase(vec.begin());

    std::cout << "Eliminate Third(Ref counter 1->0)" << std::endl;
    vec.erase(vec.begin());

    std::cout << "------ && ------" << std::endl;
    std::shared_ptr<A> p1(new A());
    std::shared_ptr<A> p2(p1);

    std::cout << p1.use_count() << std::endl;
    std::cout << p2.use_count() << std::endl;

    std::shared_ptr<A> p3(p2);
    std::cout << p1.use_count() << std::endl;
    std::cout << p2.use_count() << std::endl;

    std::cout << "------ && ------" << std::endl;
    std::shared_ptr<A> s1 = std::make_shared<A>();

    std::cout << "------ && ------" << std::endl;
    // A* a = new A();
    // *NOTICE* don't allocate pointer with shared_ptr
    // std::shared_ptr<A> pal1(a);
    // std::shared_ptr<A> pal2(a);
    
    // std::cout << pal1.use_count() << std::endl;
    // std::cout << pal2.use_count() << std::endl;

    std::cout << "------ && ------" << std::endl;
    std::shared_ptr<A> pal1 = std::make_shared<A>();
    std::shared_ptr<A> pal2 = pal1 -> get_shared_ptr();

    std::cout << "PROCESS_END" << std::endl;
}