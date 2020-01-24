

class MyString {
    char* string_content;
    int string_length;

    public:  
        MyString(char c);
        MyString(const char* str);
        MyString(const MyString& str);
};
MyString::MyString(char c) {
    string_content = new char[1];
    string_content[0] = c;
    string_length = 1;
}
MyString::MyString(const char* str) {
    
}