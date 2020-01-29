#include <iostream>
#include <string>

class Employee {
    std::string name;
};

int main() {
    std::string s = "abc";

    std::cout << s << std::endl;
    std::cout << s.length() << std::endl;
    std::cout << s.max_size() << std::endl;
    std::cout << s+s << std::endl;
    
    
    return 0;
}