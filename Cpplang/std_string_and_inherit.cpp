#include <iostream>
#include <string>

class Employee {
    std::string name;
    int age;

    std::string position;
    int rank;

    public:  
        // constructor
        Employee(std::string name, int age, std::string position, int rank): name(name), age(age), position(position), rank(rank) {}
        // copy constructor
        Employee(const Employee& employee) {
            name = employee.name;
            age = employee.age;
            position = employee.position;
            rank = employee.rank;
        }
        // default constructor
        Employee() {}

        int calculate_pay() {return 200 + rank * 50;}
        void print_info() {
            std::cout << name << " (" << position << " , " << age << ") ==> " 
            << calculate_pay() << "$" << std::endl;
        }
};

class EmployeeList {
    int alloc_employee;
    int current_employee;
    Employee** employee_list;

    public:  
        EmployeeList(int alloc_employee): alloc_employee(alloc_employee) {
            employee_list = new Employee*[alloc_employee];
            current_employee = 0;
        }
        void add_employee(Employee* employee) {
            employee_list[current_employee] = employee;
            current_employee++;
        }
        int current_employee_num() {return current_employee;}

        void print_employee_info() {
            int total_pay = 0;
            for (int i = 0; i < current_employee; i++) {
                employee_list[i] -> print_info();
                total_pay += employee_list[i] -> calculate_pay();
            }
            std::cout << "Total cost : " << total_pay << "$" << std::endl;
        }
        ~EmployeeList() {
            for (int i = 0; i < current_employee; i++) {
                delete employee_list[i];
            }
            delete[] employee_list;
        }
};

int main() {
    std::string s = "abc";

    std::cout << s << std::endl;
    std::cout << s.length() << std::endl;
    std::cout << s.max_size() << std::endl;
    std::cout << s+s << std::endl;
    std::cout << std::endl;

    EmployeeList emp_list(10);

    return 0;
}