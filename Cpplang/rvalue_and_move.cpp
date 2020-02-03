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

void swapper(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    A a(1);
    A b(a);
    // Copy ellision
    A c(A(2));

    MyString str1("abc");
    MyString str2("tfg");
    MyString str3 = str1 + str2;
    str3.println();

    std::cout << "--------------------------------" << std::endl;
    MyString s("abc");
    std::vector<MyString> vec;
    vec.resize(0);
    std::cout << "-&-" << std::endl;
    vec.push_back(s);
    std::cout << "-&-" << std::endl;
    vec.push_back(s);
    std::cout << "-&-" << std::endl;
    vec.push_back(s);

}