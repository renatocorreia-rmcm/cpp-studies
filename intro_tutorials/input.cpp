#include <iostream>

int main(){

    std::cout << "type 2 words ";
    std::string name;
    std::cin >> name;  //character input  // >> = input  //will stop on first space " "
    std::cout << "you typed " << name << "\n";

    std::cout << "type 2 words again: ";
    std::getline(std::cin, name);  // get full line
    std::cout << "you typed" << name << "\n";

    std::cout << "type 2 words again: ";
    std::getline(std::cin >>  std::ws, name);  //std::ws remove any lasting string from previus inputs
    std::cout << "you typed " << name << "\n";


    return 0;  //reach return 0; means that we have no problem running the program, instead of return 1;
}
