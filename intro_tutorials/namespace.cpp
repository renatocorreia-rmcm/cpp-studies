#include <iostream>

//namespace = prevent name conflicts, different namespaces can have different variables named the same way
namespace example1 {
    int a = 1;
}
namespace example2 {
    int a = 2;
}

int main(){
    /* 
        :: = scope resolution operator - set entitie namespace
        all std:: could be taken of by using: using namespace std; or: using std::cout; and any other especific entitie
    */

    int a = 0;
    std::cout << a << example1::a << example2::a << '\n';

    return 0;
}
