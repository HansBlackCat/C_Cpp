#include <iostream>
#include <string>

template <typename T> 
void print(T arg) {
    std::cout << arg << std::endl;
}

// Template Parameter Pack
template <typename T, typename... Types>
void print(T arg, Types... args) {
    std::cout << arg << ", ";
    print(args...);
}

// typedef unsigned long size_t
size_t GetStringSize(const char* s) {return strlen(s);}
size_t GetStringSize(const std::string& s) {return s.size();}

template <typename S, typename... Ss>
size_t GetStringSize(const S& string, Ss... strings) {
    return GetStringSize(string) + GetStringSize(strings...);
}

void AppendToString(std::string* const_str) {return;}

template <typename Str, typename... Strs>  
void AppendToString(std::string* constr_str, const Str& s, Strs... ss) {
    constr_str -> append(s);
    AppendToString(constr_str, ss...);
}

template <typename S>  
std::string StrCat(const S& s) {
    return std::string(s);
}  

template <typename S, typename... Ss> 
std::string StrCat(const S& s, Ss... strs) {
    size_t total_size = GetStringSize(s, strs...);
    std::string concat_str;
    concat_str.reserve(total_size);

    concat_str = s;
    AppendToString(&concat_str, strs...);
    return concat_str;
}

///
///
///
int sum_all() {return 0;}

template <typename... Ints>  
int sum_all(int num, Ints... nums) {
    return num + sum_all(nums...);
}
template <typename... Doubles> 
double average(Doubles... nums) {
    return static_cast<double>(sum_all(nums...)) / static_cast<double>(sizeof...(nums));
}

///
/// C++17 Foldl Expression
///
int sum_fold() {return 0;}
template <typename... Ints>  
int sum_fold(Ints... nums) {
    return (... + nums);
}

template <typename Int, typename... Ints>  
Int diff_from(Int start, Ints... nums) {
    return (start - ... - nums);
}

class A {
    public:  
        void do_something(int x) const {
            std::cout << "Do something with " << x << std::endl;
        }
};
template <typename T, typename... Ints>  
void do_many_things(const T& t, Ints... nums) {
    (t.do_something(nums), ...);
}

int main() {
    print(1, 3.1, "abc");
    print(1, 2, 3, 4, 5, 6, 7);


    std::string s1 = "abc";
    std::string s2 = "ABC";
    std::string s3("012");
    std::string concat;
    concat.reserve(s1.size()+s2.size()+s3.size());
    concat.append(s1);
    concat.append(s2);
    concat.append(s3);
    std::cout << concat << std::endl;
    std::cout << std::endl;

    std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"),
        " ", std::string("sentence"));
    std::cout << std::endl;

    std::cout << average(1, 4, 5, 6, 7, 8) << std::endl;
    std::cout << std::endl;

    std::cout << sum_fold(1, 2, 4, 3, 43, 7) << std::endl;
    std::cout << std::endl;

    std::cout << diff_from(100, 1, 4, 6, 12) << std::endl;
    std::cout << std::endl;

    A a;
    do_many_things(a, 1, 4, 12, 9);
}
