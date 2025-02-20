#include <iostream>

int main(){
    std::string name = "jairo macaneta";

    std::cout << name.length() << "\n";

    std::cout << name.append("@gmail.com") << "\n";
    std::cout << name.insert(4, "a") << "\n";  // index, string
    std::cout << name.erase(name.find(" "), 1) << "\n";  //erase(startIndex, length)

    std::cout << name.at(2) << "\n";  //char index
    std::cout << name.find("@") << "\n";

    name.clear();
    std::cout << name.empty() << "\n";

    return 0;
}