#include <iostream>
template <typename dataType1, typename dataType2>

//can be used to generate datatype overloads

auto sum(dataType1 num1, dataType2 num2){
    return num1+num2;
}

int main(){

    std::cout << sum(1.21,1) << "\n";
    std::cout << sum(1.44,1.56) << "\n";
    std::cout << sum(2,-0.5) << "\n";

    return 0;
}
