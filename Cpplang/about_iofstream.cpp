#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

int main() {
    std::ifstream ifs("about_iofstream_test.txt");
    std::string s;

    if (ifs.is_open()) {
        ifs >> s;
        std::cout << "String Input: " << s << std::endl;
    } else {
        std::cout << "Cannot find File" << std::endl;
    }

    ifs.close();
    ifs.open("other.txt");

    

    return 0;
}