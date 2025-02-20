#include <iostream>

// feature that allows functions and classes to operate with generic types

template <typename t>
t square(t num){
    return num*num;
}

int main(){

    std::cout<<square(12)<<std::endl;
    std::cout<<square(1.1)<<std::endl;

    //side effect: code bloat = the function for int and float, for example, are differents, and ocuppy their own space
        //the presence of program code (source code or machine code) that is perceived as unnecessarily long, slow, or otherwise wasteful of resources

    return 0;
}
