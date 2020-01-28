#include <iostream>
#include <string.h>

using namespace std;

int main() {
    int a, b;

    int temp = 3;
    const int con_temp = temp;
    cout << "temp, con_temp: " << temp << ", " << con_temp << endl;
    cout << "Each point?: " << &temp << ", " << &con_temp <<endl;
    temp += 3;
    cout << "temp, con_temp: " << temp << ", " << con_temp << endl;
    cout << "Each point?: " << &temp << ", " << &con_temp <<endl;

    cout << endl;

    const int* pa = &a;
    cout << pa << endl;
    // *pa = 3;
    pa = &b;
    cout << pa << endl;
    a = 4;
    cout << pa << endl;

    std::cout << pa << std::endl;

    cout << endl;

    int* const ppa = &a;
    cout << ppa << endl;
    *ppa = 3;
    cout << ppa << endl;
    // ppa = &b;


    return 0;
}
