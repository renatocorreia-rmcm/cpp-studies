#include <iostream>

void printNum();
int x = 1;
int y = 2;

int main(){
    int x = 3;

    std::cout << x << "\n";
    std::cout << y << "\n";
    std::cout << ::x << "\n";
    printNum();

    return 0;
}

void printNum(){
    int x = 4;
    std::cout << x << "\n";
}