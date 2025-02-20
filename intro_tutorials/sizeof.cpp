#include <iostream>

int main(){
    std::cout << "sizes in bytes (1 byte = 8 bits)" << "\n";

    std::cout << sizeof(bool) << "\n";
    std::cout << sizeof(char) << "\n";
    std::cout << sizeof(int) << "\n";
    std::cout << sizeof(double) << "\n";
    std::cout << sizeof(std::string) << "\n";
    
    std::cout << sizeof(true) << "\n";
    std::cout << sizeof('a') << "\n";
    std::cout << sizeof(12) << "\n";
    std::cout << sizeof(1.44) << "\n";

    std::string word = "string !";
    std::cout << sizeof(word) << "\n";  //string is reference type: holds an adress for where the text is located  //so this will pass the size of the adress not the size of the string itself
    std::cout << sizeof("string !") << "\n";  //size of the string itself
    
    char charArray[] = {'A','b','c','d','E','f'};
    std::cout << sizeof(charArray) << "\n";  //6 char with 1byte each = 6bytes

    std::string stringArray[] = {"dog", "sheep", "pig"};
    std::cout << sizeof(stringArray)/sizeof(std::string) << " items" << "\n";

    return 0;
}