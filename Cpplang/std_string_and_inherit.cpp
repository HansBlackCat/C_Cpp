#include <iostream>
#include <string>

class Employee {
    protected:  
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
class Manager: public Employee {
    int year_of_service;

    public:  
        Manager(std::string name, int age, std::string position, int rank, int year_of_service)
            : year_of_service(year_of_service), Employee(name, age, position, rank) {}
        Manager(const Manager& manager)
            :Employee(manager.name, manager.age, manager.position, manager.rank) {
                year_of_service = manager.year_of_service;
            }
        Manager(): Employee() {}
};

class EmployeeList {
    int alloc_employee;
    int current_employee;
    int current_manager;
    Employee** employee_list;
    Manager** manager_list;

    public:  
        EmployeeList(int alloc_employee): alloc_employee(alloc_employee) {
            employee_list = new Employee*[alloc_employee];
            manager_list = new Manager*[alloc_employee];
            current_employee = 0;
            current_manager = 0;
        }
        void add_employee(Employee* employee) {
            employee_list[current_employee] = employee;
            current_employee++;
        }
        void add_manager(Manager* manager) {
            manager_list[current_manager] = manager;
            current_manager++;
        }
        int current_employee_num() {return current_employee+current_manager;}

        void print_employee_info() {
            int total_pay = 0;
            for (int i = 0; i < current_employee; i++) {
                employee_list[i] -> print_info();
                total_pay += employee_list[i] -> calculate_pay();
            }
            for (int i = 0; i < current_manager; i++) {
                manager_list[i] -> print_info();
                total_pay += manager_list[i] ->calculate_pay();
            }
            std::cout << "Total cost : " << total_pay << "$" << std::endl;
        }
        ~EmployeeList() {
            for (int i = 0; i < current_employee; i++) {
                delete employee_list[i];
            }
            for (int i = 0; i < current_manager; i++) {
                delete manager_list[i];
            }
            delete[] employee_list;
            delete[] manager_list;
        }
};

//
// Base - Derived Test
//
class Base {
    protected:  
        std::string parent_string;
    public:  
        Base(): parent_string("Base") {std::cout<<"Base Class"<<std::endl;}
        void what() {std::cout<<parent_string<<std::endl;}
};
class Derived: public Base {
    std::string child_string;

    public:  
        Derived(): Base(), child_string("Derived") {
            std::cout<<"Derived Class"<<std::endl;
            parent_string = "What?";
            what();
        }
        // overriding what()
        void what() {std::cout<<child_string<<std::endl;}
};
//
//
//

int main() {
    std::string s = "abc";

    std::cout << s << std::endl;
    std::cout << s.length() << std::endl;
    std::cout << s.max_size() << std::endl;
    std::cout << s+s << std::endl;
    std::cout << std::endl;

    EmployeeList emp_list(10);
    emp_list.add_employee(new Employee("Kate", 32, "Norm", 1));
    emp_list.add_employee(new Employee("Zun", 38, "Norm", 1));
    emp_list.add_employee(new Employee("Baba", 47, "Maj", 7));
    emp_list.add_employee(new Employee("Stru", 44, "Jo", 3));

    emp_list.print_employee_info();
    std::cout<<std::endl;

    Base p;
    std::cout<<std::endl;
    Derived q;

    std::cout << "\n<<Pointer Ver>>" <<std::endl;
    Base* p_p = &q;
    p_p -> what();

    // !! DownCasting is Dangerous !!
    Derived* p_q = static_cast<Derived*>(p_p);

    // Dynamic Cast
    // Derived* d_q = dynamic_cast<Derived*>(p_p);    


    return 0;
}