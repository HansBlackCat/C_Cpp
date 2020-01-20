#include <iostream>
#include <vector>
#include <string>

void print_square(int x);
int change_value(int* x);
int change_val(int x);
int change_ref(int& p);
int fn1(int& a);
int& fn2(int& a);

int main()
{
    std::cout << "Hello, World!!" << std::endl;

    int arr[10];
    int* parr = arr;

    for (int i =0; i<10; i++) {
        std::cout << i;
    }
    std::cout<< "\n" <<std::endl;

    print_square(3);
    std::cout << std::endl; 

    int change_ref_num = 10;
    change_val(change_ref_num);
    std::cout << change_ref_num << std::endl;
    change_value(&change_ref_num);
    std::cout << change_ref_num << std::endl;
    change_ref(change_ref_num);
    std::cout << change_ref_num << std::endl;
    std::cout << std::endl;
    
    int ref_a = 4;
    int& ref_b = ref_a;
    int* ptr_a = &ref_a;
    int* ptr_b = &ref_b;
    int ref_c = 10;
    ref_b = ref_c;

    const int& ref = 5;

    int x = 1;
    std::cout << x << " -(fn2++)-> " << fn2(x)++ << std::endl;
    std::cout << std::endl;

    

    /*
    int magic_number = 7;
    int user_input;
    while (true) {
        std::cout << "Input: ";
        std::cin >> user_input;
        std::cout << user_input << std::endl;
        if (user_input == magic_number) {
            std::cout << "Youre right!" << std::endl;
            break;
        } else { 
            std::cout << "Youre wrong!" << std::endl;
            continue;
        }
    }
    */
}

void print_square(int x) {
    std::cout << "Result: " << x*x << std::endl;
}

int change_value(int* p) {
    *p = 3;
    return 0;
}
int change_val(int p) {
    p = 3;
    return 0;
}
int change_ref(int& p) {
    p += 10;
    return 0;
}

int fn1(int& a) { return a; }
int& fn2(int& a) { return a; }