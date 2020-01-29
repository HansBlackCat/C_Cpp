#include <iostream>

class Array {
    const int dim; // Tree depth
    int* size; // Branch Num in array

    // Apple Structure
    struct Address {
        int level; // current location(depth)
        void* next; // into deep
    };
    // Root
    Address* top;
    
    public:  
        Array(int dim, int* array_size): dim(dim) {
            size = new int[dim];
            for (int i = 0; i < dim; i++) size[i] = array_size[i];
        }
        
        //
        void initialize_address(Address* current) {
            if (!current) return;
            if(current -> level == dim - 1) {
                current -> next = new int[size[current -> level]];
                return;
            }
            current -> next = new Address[size[current -> level]];
            for (int i = 0; i != size[current -> level]; i++) {
                (static_cast<Address*>(current -> next) + i) -> level = current -> level + 1;
                initialize_address(static_cast<Address*>(current -> next) + i);
            }
        }
        void delete_address(Address* current) {
            if (!current) return;
            for (int i = 0; current -> level < dim - 1 && i < size[current -> level]; i++) {
                delete_address(static_cast<Address*>(current -> next) + i);
            }
            delete[] static_cast<Address*>(current -> next);
        }
        ~Array() {
            delete_address(top);
            delete[] size;
        }

        /*
        void initialize_address(Address* current);
        void delete_address(Address* current);
        */
};
/*
void Array::initialize_address(Array::Address* current) {
    if (!current) return;
    if (current -> level == dim - 1) {
        current -> next = new int[size[current -> level]];
        return;
    }
    current -> next = new Address[size[current -> level]];
    for (int i = 0; i != size[current -> level]; i++) {
        (static_cast<Address*>(current -> next) + i) -> level = current -> level + 1;
        initialize_address(static_cast<Address*>(current -> next) + i);
    }
}

void Array::delete_address(Array::Address* current) {
    if(!current) return;
    for (int i = 0; current -> level < dim - 1 && i < size[current -> level]; i++) {
        delete_address(static_cast<Address*>(current -> next) + i);
    }
    delete[] current -> next;
}*/


int main() {
    float floaty = 3.14;
    int inty = static_cast<int>(floaty);

    std::cout<<inty<<std::endl;

    // Simple bin tree array
    int x1 = 4, x2 = 4;
    int** arr;
    arr = new int*[x1];
    for (int i = 0; i < x1; i++) arr[i] = new int[x2];

    std::cout<<"END_PROCESS"<<std::endl;
}