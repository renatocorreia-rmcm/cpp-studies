#include <iostream>
#include <cmath>

int main(){
    srand(time(NULL));  //rand() would always return the same num without this (why?)

    std::cout << rand() << "\n";  // 0 - 32767

    std::cout << (rand() % 6) + 1 << "\n";
    std::cout << round(((double)rand()/32767)*6) << "\n";


    return 0;
}