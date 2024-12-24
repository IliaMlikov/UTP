#include <iostream>


int main(){
    const int size = 5; 
    int array[size];
    for (int i = 0; i < size; i++) {
        std::cin >> array[i];
        std::cout<< array[i];
    }

}