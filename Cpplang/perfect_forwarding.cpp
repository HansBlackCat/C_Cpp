#include <iostream>
#include <string>
#include <vector>

class A {
    int _data;

    public:  
        A(int data): _data(data) {std::cout<<"Normal Constructor!"<<std::endl;}
        A(const A& a): _data(a._data) {std::cout<<"Copy Constructor!"<<std::endl;}
};

class MyString {
    char* string_content;
    int string_length;
    int memory_capacity;

    public:  
        MyString();
        MyString(const char* str);
        // Copy Inititalize
        MyString(const MyString& str);
        // Move Inititalize
        // Reference of *RVALE* (special case)
        // `noexcept` prevent container from not using Move Inititalizer
        MyString(MyString&& str) noexcept;
        ~MyString();

        void reserve(int size);
        MyString operator+(const MyString& string2);
        MyString& operator=(const MyString& s);
        // Operator Overload for move
        MyString& operator=(MyString&& s);

        int length() const;
        void print();
        void println();
};
MyString::MyString() {
    std::cout << "Call Initializer!" << std::endl;
    string_length = 0;
    memory_capacity = 0;
    string_content = nullptr;
}
MyString::MyString(const char* str) {
    std::cout << "String Inititalizer!" << std::endl;
    string_length = strlen(str);
    memory_capacity = 2 * strlen(str);
    string_content = new char[string_length];
    for (int i = 0; i < string_length; i++) {
        string_content[i] = str[i];
    }
}
MyString::MyString(const MyString& cpyClass) {
    std::cout << "Copy Initializer!" << std::endl;
    string_length = cpyClass.string_length;
    memory_capacity = cpyClass.memory_capacity;
    string_content = new char[string_length];
    for (int i = 0; i < string_length; i++) {
        string_content[i] = cpyClass.string_content[i];
    }
}
MyString::MyString(MyString&& obj) noexcept {
    std::cout << "Move Inititalizer!" << std::endl;
    string_length = obj.string_length;
    memory_capacity = obj.memory_capacity;
    string_content = obj.string_content;
    // Don't let temporary obj die
    obj.string_content = nullptr;
}
MyString::~MyString() {
    // Prevent 'move constructor' to delete itself
    if (string_content) delete[] string_content;
}
void MyString::reserve(int size) {
    if (size > memory_capacity) {
        char* temp_content = string_content;
        string_content = new char[size];
        memory_capacity = size;

        for (int i = 0; i < string_length; i++) {
            string_content[i] = temp_content[i];
        }
        if (temp_content != nullptr) delete[] temp_content;
    }
}
MyString MyString::operator+(const MyString& s) {
    MyString str;
    str.reserve(memory_capacity + s.memory_capacity);
    for (int i = 0; i < string_length; i++) 
        str.string_content[i] = string_content[i];
    for (int i = string_length; i < string_length + s.string_length; i++)
        str.string_content[i] = s.string_content[i-string_length];
    str.string_length = string_length + s.string_length;
    return str;
}
MyString& MyString::operator=(const MyString& s) {
    std::cout << "Copy operator!" << std::endl;
    if (s.string_length > memory_capacity) {
        delete[] string_content;
        string_content = new char[2*s.string_length];
        memory_capacity = 2 * s.string_length;
    }
    for (int i = 0; i < s.string_length; i++) {
        string_content[i] = s.string_content[i];
    }
    return* this;
}
MyString& MyString::operator=(MyString&& s) {
    std::cout << "Move operator" << std::endl;
    string_content = s.string_content;
    memory_capacity = s.memory_capacity;
    string_length = s.string_length;

    s.string_content = nullptr;
    s.memory_capacity = 0;
    s.string_length = 0;
    return* this;
}

int MyString::length() const {return string_length;}
void MyString::print() {
    for (int i = 0; i < string_length; i ++) {
        std::cout << string_content[i];
    }
}
void MyString::println() {
    this -> print();
    std::cout << std::endl;
}

template <typename T>  
void my_swap(T& a, T& b) {
    T temp(a);
    a = b;
    b = temp;
}
template <>  
void my_swap<MyString>(MyString& a, MyString& b) {
    MyString temp(std::move(a));
    a = std::move(b);
    b = std::move(temp);
}

class AT {
    int value;

    public:  
        AT(int a): value(a) {};
        friend std::ostream& operator<<(std::ostream& os, const AT& cons) {
            os << cons.value;
            return os;
        }
};

template <typename T>  
void Wrapper(T u) {
    g(u);
}
template <typename T>  
void Wrapper_fix(T& u) {
    std::cout << "~ Infer T& ~" << std::endl;
    g(u);
}
template <typename T>  
void Wrapper_fix(const T& u) {
    std::cout << "~ Infer const T& ~" << std::endl;
    g(u);
}
template <typename T>
// T&& is *NOT* rval reference!!
// Universal reference
// Template-type && reference -> universal reference
void Wrapper_universal(T&& u) {
    std::cout << "~ Universal infer T&& ~" << std::endl;
    // use std::move only if rval
    g(std::forward<T>(u));
}
class A_w {};
void g(A_w& a) {std::cout << "Call lval ref" << std::endl;}
void g(const A_w& a) {std::cout << "Call const lval ref" << std::endl;}
void g(A_w&& a) {std::cout << "Call rval ref" << std::endl;}

int main() {
    std::cout << "--- Init ---" << std::endl;
    MyString str1("abc");

    std::cout << "--- Before move ---" << std::endl;
    str1.println();
    
    std::cout << "--- After move ---" << std::endl;
    // Move lvalue to rvalue
    MyString str2(std::move(str1));
    // Segfault (nullptr called)
    // str1.println();
    str2.println();

    std::cout << "---------- & ----------" << std::endl;
    MyString str3("abc");
    MyString str4("def");
    std::cout << "--- Before Swap ---" << std::endl;
    str3.println();
    str4.println();
    std::cout << "--- After Swap ---" << std::endl;
    my_swap(str3, str4);
    str3.println();
    str4.println();

    std::cout << "---------- & ----------" << std::endl;
    std::vector<AT> vec1;
    AT at1(1);
    AT at2(2);
    AT at3(3);
    vec1.push_back(at1);
    vec1.emplace_back(4);
    std::cout << "emplace test" << std::endl;

    std::cout << "---------- & ----------" << std::endl;
    A_w a_w;
    const A_w a_wc;
    std::cout << "-- Original --" << std::endl;
    g(a_w);
    g(a_wc);
    g(A_w());

    std::cout << "-- Wrapper --" << std::endl;
    Wrapper(a_w);
    Wrapper(a_wc);
    Wrapper(A_w());

    std::cout << "-- Wrapper_fix --" << std::endl;
    Wrapper_fix(a_w);
    Wrapper_fix(a_wc);
    Wrapper_fix(A_w());

    std::cout << "-- Wrapper_fix --" << std::endl;
    Wrapper_universal(a_w);
    Wrapper_universal(a_wc);
    Wrapper_universal(A_w());

    std::cout << "\nEND_PROCESS" << std::endl;
}