#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <string>

template <typename Iter> 
void print(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << *begin << " ";
        begin++;
    }
    std::cout << std::endl;
}

struct rev_compare_functor {
    bool operator()(const int& a, const int& b) const {
        return a>b;
    }
};

struct is_odd {
    bool operator()(const int& i) const {return i%2==1;}
};

// Ref Member vari
struct is_odd_two {
    int delete_num;
    is_odd_two(): delete_num(0) {};

    bool operator()(const int& a) {
        if (delete_num<2 && a%2==1) {
            delete_num++;
            return true;
        } else {
            return false;
        }
    };
};
// Ref Field vari
struct is_odd_two_safe {
    int* delete_num;
    is_odd_two_safe(int* _delete_num): delete_num(_delete_num) {};

    bool operator()(const int& a) {
        if (*delete_num<2 && a%2==1) {
           (*delete_num)++;
            return true;
        } else {
            return false;
        }
    };
};

bool odd(const int& i) {return i%2==1;}

int main() {
    std::vector<int> vec = {5, 3, 7, 2, 13, 7, 0};
    print(vec.begin(), vec.end());

    // Available Only RandomAccessableIterator
    std::sort(vec.begin(), vec.end());
    print(vec.begin(), vec.end());

    std::sort(vec.begin(), vec.end(), rev_compare_functor());
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    print(vec.begin(), vec.end());
    std::cout << std::endl;
    
    std::vector<int> vec2 = {5, 3, 7, 2, 13, 7, 0};
    std::partial_sort(vec2.begin(), vec2.begin()+3, vec2.end());
    print(vec2.begin(), vec2.end());



    std::vector<int> vec3 = {5, 3, 7, 2, 13, 7, 0};
    // Remove value 3
    // std::remove -> ForwardIterator
    vec3.erase(std::remove(vec3.begin(), vec3.end(), 3), vec3.end());
    print(vec3.begin(), vec3.end());

    // Remove odd num
    vec3.erase(std::remove_if(vec3.begin(), vec3.end(), is_odd()), vec3.end());
    vec3.erase(std::remove_if(vec3.begin(), vec3.end(), odd), vec3.end());
    print(vec3.begin(), vec3.end());
    
    // Very Dangerous Approach, cause Pred func change it's condition
    // std::vector<int> vec4 = {5, 3, 7, 2, 13, 7, 0};
    // vec4.erase(std::remove_if(vec4.begin(), vec4.end(), is_odd_two()), vec4.end());
    // print(vec4.begin(), vec4.end());

    std::vector<int> vec4 = {5, 3, 7, 2, 13, 7, 0};
    int _init_delete_num = 0;
    vec4.erase(std::remove_if(vec4.begin(), vec4.end(), is_odd_two_safe(&_init_delete_num)), vec4.end());
    print(vec4.begin(), vec4.end());

    // Lambda
    std::vector<int> vec5 = {5, 3, 7, 2, 13, 7, 0};
    vec5.erase(std::remove_if(vec5.begin(), vec5.end(),
        // Lambda function
        [](int i) -> bool {return i%2==1;}),
        vec5.end());
    print(vec5.begin(), vec5.end());

    int lambda_test_int = 9;
    std::cout << "--Lambda Test--\n> " << 
        // Capture list test
        // & mean capture `reference`
        // without & mean `copy` (const copy, can't mut)
        [&lambda_test_int](int i)->int {lambda_test_int++; return i+lambda_test_int;}(10) << std::endl;
    std::cout << "--lambda_test_int--\n> " <<
        lambda_test_int << std::endl;
}