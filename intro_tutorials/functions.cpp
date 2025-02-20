#include <iostream>

void greet(){
    std::cout << "fuck yourself" << "\n";
}
void greet(std::string name = "mf"){  // overload
    std::cout << "fuck yourself " << name << "\n";
}

int sum(const int a, const int b);  //must be declared before main, assignment can be after  //const parameters are optional

int main(){
    greet("dog");
    std::cout << sum(1, 2) << "\n";

    return 0;
}

int sum(const int a, const int b){
    //a += 3;  //error
    return a+b;
}