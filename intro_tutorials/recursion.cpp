#include <iostream>

//recursion: programming technique where a function invoke itself from within
//less code, cleaner, useful for sorting and searching
//uses more memory, slower

int factorial(int num);

int main(){
    std::cout << factorial(5);

    return 0;
}

int factorial(int num){
    if(num>1){
        return num*factorial(num-1);
    }
    else{
        return 1;
    }
}