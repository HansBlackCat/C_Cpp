/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        printf("Rnd: %d \n", rand() % 100);
    }

}
*/
#include <iostream>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dis(0, 99);

    for (int i = 0; i < 5; i++) {
        std::cout << "Rnd: " << dis(gen) << std::endl;
    }
}
