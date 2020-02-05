#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

template <typename T> 
void print_vector(std::vector<T>& vec) {
    for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end(); itr++) {
        std::cout << *itr << " ";
    }
    std::cout << std::endl;
}

template <typename T> 
void print_deque(std::deque<T>& deq) {
    for (const auto& elem: deq) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template <typename T, typename U> 
void print_set(std::set<T, U>& sett) {
    for (const auto& elem: sett) {
        std::cout << elem << " ";
    }
}
template <typename T> 
void print_set(std::set<T>& sett) {
    for (const auto& elem: sett) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

class Todo {
    int priority;
    std::string content;

    public: 
        Todo(int _priority, std::string _content): priority(_priority), content(_content) {};

        bool operator<(const Todo& t) const;
        friend std::ostream& operator<<(std::ostream& os, const Todo& todos);
};
bool Todo::operator<(const Todo& t) const {
    if (priority == t.priority) {
        return content < t.content;
    }
    return priority > t.priority;
}
std::ostream& operator<<(std::ostream& os, const Todo& todos) {
    os << "[Priority: " << todos.priority << "] " << todos.content;
    return os;
}

class Todo_without_operator {
    int priority;
    std::string content;

    public: 
        Todo_without_operator(int _priority, std::string _content): priority(_priority), content(_content) {};

        friend struct Todo_comp;
        friend std::ostream& operator<<(std::ostream& os, const Todo_without_operator& todos) {
            os << "[Priority: " << todos.priority << "]" << todos.content;
            return os;
        }
};
struct Todo_comp {
    bool operator()(const Todo_without_operator& t1, const Todo_without_operator& t2) const {
        if (t1.priority == t2.priority) {
            return t1.content < t2.content;
        }
        return t1.priority > t2.priority;
    }
};

template <typename T, typename U> 
void print_map(std::map<T, U>& m) {
    for (auto iter = m.begin(); iter!= m.end(); iter++) {
        std::cout << iter -> first << " " << iter -> second << std::endl;
    }
    /*
     * for (const auto& elem: m) {
     *     std::cout << elem.first << " " << elem.second << std::endl;
     * }
     */
}

template <typename T, typename U> 
void print_multimap(const std::multimap<T, U>& m) {
    for (auto iter = m.begin(); iter != m.end(); iter++) {
        std::cout << iter -> first << ": " << iter -> second << std::endl;
    }
}

template <typename T> 
void print_unordered_set(const std::unordered_set<T>& m) {
    for (const auto& elem: m) {
        std::cout << elem << std::endl;
    }
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};

    for (const auto& elem: vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++) {
        std::cout << *itr << " ";
    }
    std::cout << std::endl;

    std::vector<int>::iterator itr = vec.begin() + 3;
    std::cout << "vec.begin()+3: " << *itr << std::endl;

    for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++) {
        if (*itr == 5) {
            vec.erase(itr);
            itr = vec.begin();
        }
    }
    for (const auto& elem: vec) {
        std::cout << elem << " ";
    }

    for (std::vector<int>::size_type i = 0; i != vec.size(); i++) {
        if (vec[i] == 6) {
            vec.erase(vec.begin() + i);
            i--;
        }
    }
    std::cout << "\n" << std::endl;



    // Deque -------------------------------------------------
    std::deque<int> deq = {10, 20, 30, 40, 50};
    print_deque(deq);
    deq.pop_back();
    deq.pop_front();
    deq.push_front(45);
    print_deque(deq);
    std::cout << "\n" << std::endl;



    // Set -------------------------------------------------
    std::set<int> settee = {10, 50, 40, 25, 99};
    print_set(settee);
    
    // type:  std::set<>::iterator
    auto set_finder = settee.find(40);
    if (set_finder == settee.end()) {
        std::cout << "Nope" << std::endl;
    } else {
        std::cout << "Yep: " << *set_finder << std::endl;
    }

    settee.insert(30);
    settee.insert(85);
    settee.insert(50);
    print_set(settee);

    std::set<Todo> todos;
    todos.insert(Todo(1, "Python"));
    todos.insert(Todo(5, "Haskell"));
    todos.insert(Todo(6, "Rust"));
    print_set(todos);

    std::set<Todo_without_operator, Todo_comp> todous;
    todous.insert(Todo_without_operator(5, "Rang"));
    todous.insert(Todo_without_operator(10, "Kon"));
    todous.insert(Todo_without_operator(5, "Key"));
    print_set(todous);
    std::cout << "\n" << std::endl;



    // Map -------------------------------------------------
    std::map<std::string, double> fasta_speed;
    fasta_speed.insert(std::pair<std::string, double>("Haskell", 1.40));
    fasta_speed.insert(std::pair<std::string, double>("C++", 1.46));
    fasta_speed.insert(std::pair<std::string, double>("Rust", 1.51));
    // Alternative 1
    fasta_speed.insert(std::make_pair("C#", 1.70));
    // Alternative 2
    fasta_speed["Go"] = 2.08;

    print_map(fasta_speed);
    std::cout << fasta_speed["Haskell"] << std::endl;
    // Using [] may make map confused
    // Default init with 0
    std::cout << fasta_speed["F#"] << std::endl;
    
    std::vector<std::string> names = {"Haskell", "Ocaml", "C#", "C++"};
    for (const auto& elem: names) {
        auto fasta_itr = fasta_speed.find(elem);    
        if (fasta_itr != fasta_speed.end()) {
            std::cout << fasta_itr -> second << std::endl;
        } else {
            std::cout << "None" << std::endl;
        }
    }

    // Multi-set & Multi-map ---------------------------------
    // Allow duplicated
    std::multimap<int, std::string> m;
    m.insert(std::make_pair(1.40, "Haskell"));
    m.insert(std::make_pair(1.46, "C++"));
    m.insert(std::make_pair(1.46, "C"));
    m.insert(std::make_pair(1.51, "Rust"));

    // equal_range make new iter that match condition
    auto range = m.equal_range(1.46);
    for (auto iter = range.first; iter != range.second; iter++) {
        std::cout << iter -> first << ": " << iter -> second << ": " << std::endl;
    }
    std::cout << std::endl;



    // Unordered_set & _map ---------------------------------
    // Hash function
    std::unordered_set<std::string> s;
    s.insert("hi");
    s.insert("an-neung");
    s.insert("ohaio");
    s.insert("bonjour");
    s.insert("guten-tag");
    print_unordered_set(s);

    s.erase(s.find("hi"));
    print_unordered_set(s);
}