#include <iostream>
#include <string.h>

class MyString {
    char* string_content;
    int string_length;
    int memory_capacity;

    public:  
        MyString(char c);
        MyString(const char* str);
        MyString(const MyString& str);
        ~MyString();

        int length() const;
        void print() const;
        void println() const;
        int capacity() const;
        void reserve(int size);
        char at(int i) const;

        int find(int find_from, MyString& str) const;
        int find(int find_form, const char* str) const;
        int find(int find_form, char c) const;

        int compare(const MyString& str) const;

        MyString& assign(const MyString& str);
        MyString& assign(const char* str);
        MyString& insert(int loc, const MyString& str);
        MyString& insert(int loc, const char* str);
        MyString& insert(int loc, char c);
        MyString& erase(int loc, int num);

        char& operator[](const int index);
        friend std::ostream& operator<<(std::ostream& os, const MyString& s);
};
MyString::MyString(char c) {
    string_content = new char[1];
    string_content[0] = c;
    string_length = 1;
    memory_capacity = 1;
}
MyString::MyString(const char* str) {
    string_length = strlen(str);
    memory_capacity = string_length;
    string_content = new char[string_length];
    for (int i = 0; i < string_length; i++) string_content[i] = str[i];    
}
MyString::MyString(const MyString& ori_str) {
    string_length = ori_str.string_length;
    memory_capacity = ori_str.memory_capacity;
    string_content = new char[string_length];
    for (int i = 0; i < string_length; i++) string_content[i] = ori_str.string_content[i];
}
MyString::~MyString() {delete[] string_content;}

int MyString::length() const {return string_length;}
void MyString::print() const {
    for (int i = 0; i < string_length; i++) {
        std::cout << string_content[i];
    }
}
void MyString::println() const {
    for (int i = 0; i != string_length; i++) {
        std::cout << string_content[i];
    }
    std::cout << std::endl;
}

MyString& MyString::assign(const MyString& str) {
    if (str.string_length > memory_capacity) {
        delete[] this -> string_content;
        this -> string_content = new char[str.string_length];
        memory_capacity = str.string_length;
    }
    for (int i = 0; i != str.string_length; i++) {
        this -> string_content[i] = str.string_content[i];
    }
    this -> string_length = str.string_length;
    return* this;
}
MyString& MyString::assign(const char* str) {
    int temp_length = strlen(str);
    if (temp_length > memory_capacity) {
        delete[] this -> string_content;
        this -> string_content = new char[temp_length];
        memory_capacity = temp_length;
    }
    for (int i =0; i != temp_length; i++) {
        this -> string_content[i] = str[i];
    }
    this -> string_length = temp_length;
    return* this;
}
int MyString::capacity() const {return memory_capacity;}
void MyString::reserve(int usize) {
    if (usize > memory_capacity) {
        char* prev_string_content = string_content;
        string_content = new char[usize]; // without delete OK?
        memory_capacity = usize;

        for (int i = 0; i != string_length; i++) string_content[i] = prev_string_content[i];
        delete[] prev_string_content;
    }
    
}
char MyString::at(int i) const {
    if (i >= string_length || i < 0) return NULL;
    else return string_content[i];
}

MyString& MyString::insert(int loc, const MyString& str) {
    if (loc < 0 || loc > string_length) return* this;
    if (string_length + str.string_length > memory_capacity) {
        memory_capacity = string_length + str.string_length;
        char* temp_string_content = string_content;
        string_content = new char[memory_capacity];

        // loc-1 loc loc+1
        for (int i = 0; i < loc; i++) {
            string_content[i] = temp_string_content[i];
        }    
        for (int i = loc; i < loc+str.string_length; i++) {
            string_content[i] = str.string_content[i-loc];
        }
        for (int i = loc+str.string_length; i < memory_capacity; i++) {
            string_content[i] = temp_string_content[i-str.string_length];
        }
        delete[] temp_string_content;

        string_length = string_length + str.string_length;
        return* this;
    }

    for (int i = string_length - 1; i >= loc; i--) {
        string_content[i + str.string_length] = string_content[i];
    }
    for (int i = 0; i < str.string_length; i++) string_content[i+loc] = str.string_content[i];

    string_length = string_length + str.string_length;
    return* this;
}
MyString& MyString::insert(int loc, const char* str) {
    MyString temp(str);
    return this -> insert(loc, temp);
}
MyString& MyString::insert(int loc, char c) {
    MyString temp(c);
    return this -> insert(loc, temp);
}

MyString& MyString::erase(int loc, int num) {
    if (num < 0 || loc  < 0 || loc > string_length) return* this;
    for (int i = loc + num; i < string_length; i++) {
        string_content[i - num] = string_content[i];
    }
    string_length -= num;
    return* this;
}

int MyString::find(int find_from, MyString& str) const {
    int i, j;
    if (str.string_length == 0) return -1;
    for (i = find_from; i < string_length - str.string_length; i++) {
        for (j = 0; j < str.string_length; j++) {
            if (string_content[i+j] != str.string_content[j]) break;
        }
        if(j == str.string_length) return i;
    }
    return -1;
}
int MyString::find(int find_from, const char* str) const {
    MyString temp(str);
    return this -> find(find_from, temp);
}
int MyString::find(int find_from, char c) const {
    MyString temp(c);
    return this -> find(find_from, temp);
}

int MyString::compare(const MyString& str) const {
    for (int i = 0; i < std::min(string_length, str.string_length); i++) {
        if (string_content[i] > str.string_content[i]) return 1;
        else if (string_content[i] < str.string_content[i]) return -1;
    }
    if (string_length == str.string_length) return 0;
    else if (string_length > str.string_length) return 1;
    return -1;
}

char& MyString::operator[](const int index) {return string_content[index];}
std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os << "\"-*- " << str.string_content << " -*-\"";  
    return os;
}

int main() {
    MyString str1("hello world");
    MyString str2(str1);

    str1.println();
    str2.println();

    MyString stras1("very very very long string");
    stras1.reserve(30);

    std::cout << "Capacity : " << stras1.capacity() << std::endl;
    std::cout << "String length : " << stras1.length() << std::endl;
    stras1.println();
    std::cout << std::endl;

    MyString strin1("very long string");
    MyString strin2("<some string inserted between>");
    strin1.reserve(30);

    std::cout << "Capacity : " << strin1.capacity() << std::endl;
    std::cout << "String length : " << strin1.length() << std::endl;
    strin1.println();

    strin1.insert(5, strin2);
    strin1.println();
    std::cout << std::endl;

    MyString strfn1("this is a very very long string");
    std::cout << "Location of first <very> in the string : " << strfn1.find(0, "very") << std::endl;
    std::cout << "Location of second <very> in the string : " << strfn1.find(strfn1.find(0, "very")+1, "very") << std::endl;
    std::cout << std::endl;

    MyString strcmp1("abcdef");
    MyString strcmp2("abcde");
    std::cout << "strcmp1 & 2 compare : " << strcmp1.compare(strcmp2) << std::endl;

    MyString temp("abcdef");
    temp[0] = 'K';
    std::cout << temp << std::endl;

    std::cout << "MAIN END" << std::endl;

}