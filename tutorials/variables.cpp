#include <iostream>

int main(){

    int x;
    x = 12;
    std::cout << x << "\n";
    std::cout << x%5 << '\n';
    int y = x*x;
    std::cout << y << "\n";
    double z = 1.21;
    std::cout << z << "\n";
    z *= z;
    std::cout << z << "\n";
    z++;
    std::cout << z << '\n';
    char letter = 'r';  // single quotes
    std::cout << letter << "\n";
    bool surfing = true;
    std::cout << surfing << "\n";
    std::cout << false << "\n";
    std::string word = "awagaga";  //strings = objects that represents a sequence of text  //double quotes
    std::cout << word << "\n";
    std::cout << "you said " << word << "\n";

    const double pi = 3.14;  // 'read-only' variable
    std::cout << pi << "\n";

    //char firstLetter = 1100001; //implicit conversion  //ascii in this case
    //std::cout << firstLetter << "\n";
    double fi = (int) 1.68; //explicit conversion
    std::cout << fi << "\n";
    
    return 0;
}
