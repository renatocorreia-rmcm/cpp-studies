#include <iostream>

//memory adress = location in memory where data is stored
//memory adress can be accessed with & (adress-of operator)

//use & to pass variables by reference instead of value

int main(){
    std::string word = "abc def";
    int num = 3;
    bool condition = true;

    std::cout << &word << "\n";
    std::cout << &num << "\n";
    std::cout << &condition << "\n";
}