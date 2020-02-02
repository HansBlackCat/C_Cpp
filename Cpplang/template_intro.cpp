#include <iostream>
#include <string>
#include <vector>
#include <array>

template <typename T>
class Vector {
    T* data;
    int capacity;
    int length;

    public:  
        Vector(int n = 1): data(new T[n]), capacity(n), length(0) {}

        void push_back(T s) {
            if (capacity <= length) {
                T* temp = new T[capacity * 2];
                for (int i = 0; i < length; i++) {
                    temp[i] = data[i];
                }
                delete[] data;
                data = temp;
                capacity *= 2;
            }
            data[length] = s;
            length ++;
        }

        T operator[](int i) {return data[i];}

        void remove(int x) {
            for (int i = x + 1; i < length; i++) {
                data[i - 1] = data[i];
            }
            length --;
        }

        int size() {return length;}

        void swap(int i, int j) {
            T temp = data[j];
            data[j] = data[i];
            data[i] = temp;
        }

        ~Vector() {
            if (data) {delete[] data;}
        }
};

template <>
class Vector<bool> {
    unsigned int* data;
    int capacity;
    int length;

    public:  
        typedef bool value_type;

        Vector(int n = 1)
            : data(new unsigned int[n/32+1]), capacity(n/32+1), length(0) {
                for (int i = 0; i < capacity; i++) {
                    data[i] = 0;
                }
            }
        
        void push_back(bool s) {
            if (capacity * 32 <= length) {
                unsigned int* temp = new unsigned int[capacity * 2];
                for (int i = 0; i < capacity; i++) {
                    temp[i] = data[i];
                }
                for (int i = capacity; i < 2 * capacity; i++) {
                    temp[i] = 0;
                }
                delete[] data;
                data = temp;
                capacity *= 2;
            }

            if (s) {
                data[length / 32] |= (1 << (length % 32));
            }

            length ++;
        }

        void remove(int x) {
            for (int i = x+1; i < length; i++) {
                int prev = i - 1;
                int curr = i;

                if (data[curr / 32] & (1 << (curr % 32))) {
                    data[prev / 32] |= (1 << (prev % 32));
                } else {
                    unsigned int all_ones_except_prev = 0xFFFFFFFF;
                    all_ones_except_prev ^= (1 << (prev % 32));
                    data[prev / 32] &= all_ones_except_prev;
                }
            }
            length--;
        }

        int size() {return length;}

        ~Vector() {
            if (data) {
                delete[] data;
            }
        }
};

// func is *NOT* functionl, but object
// overloaded operator() from Comp Class
template <typename C, typename Func> 
void bubble_sort(C& count, Func& func) {
    for (int i = 0; i < count.size(); i++) {
        for (int j = i; j < count.size(); j++) {
            if (func(count[i], count[j])) {
                count.swap(i, j);
            }
        }
    }
}

// This is Functor class
struct Comp1
{
    bool operator()(int a, int b) {return a>b;}
};
template <typename T>
struct Comp2
{
    bool operator()(const T& a, const T& b) {return a<b;}
};

template <typename T, int num>  
T add_num(T t) {
    return t + num;
}

template <typename T>
void print_array(const T& arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <int num>  
void test_fun() {
    int temp_num = num;
    std::cout << temp_num << std::endl;
}

template <typename T>  
struct Compare
{
    bool operator()(const T& a, const T& b) const {return a<b;}
};
template <typename T, class Func = Compare<T> >
T min(T a, T b) {
    Func comp;
    if (comp(a, b)) {
        return a;
    } else {
        return b;
    }
}


int main() {

    Vector<int> int_vec;
    int_vec.push_back(3);
    int_vec.push_back(2);
    int_vec.push_back(5);
    int_vec.push_back(0);

    std::cout << int_vec[0] << std::endl;
    std::cout << int_vec[1] << std::endl;

    Comp1 comp1;
    bubble_sort(int_vec, comp1);
    for (int i = 0; i < int_vec.size(); i++) {
        std::cout << int_vec[i] << " ";
    }
    std::cout << std::endl;

    Comp2<int> comp2;
    bubble_sort(int_vec, comp2);
    for (int i = 0; i < int_vec.size(); i++) {
        std::cout << int_vec[i] << " ";
    }
    std::cout << std::endl;

    int x = 3;
    std::cout << "x: " << add_num<int, 5>(x) << std::endl;

    std::array<int, 6> arr = {1,2,3,4,5,6};
    std::array<char, 3> arr2 = {'a','b','t'};
    print_array(arr);
    print_array(arr2);

    test_fun<3>();
    std::cout << std::endl;

    int a = 3, b = 5;
    std::cout << min(a, b) << std::endl;

    std::cout << "\nEND_PROCESS" << std::endl;
    return 0;
}