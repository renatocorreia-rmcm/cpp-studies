#include <iostream>  //header file that contains functions for basic input and output  //# = preprocessor 

int main(){  //the main function is where the program begins

    std::cout << "Hello, world!";  //cout = character output  // << = output
    std::cout << "blank line after stds couts must be setted" << std::endl;  //endl = endline  //vantage = flush output buffer
    std::cout << "it is also possible to do so with the blank line character \n";  //vantage = performance
    std::cout << "or even like this" << "\n";

    return 0;  //reach return 0; means that we have no problem running the program, instead of return 1;
}
