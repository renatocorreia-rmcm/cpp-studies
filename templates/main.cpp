#include <iostream>
using namespace std;


template <typename my_t>
my_t my_max(my_t a, my_t b){
    return (a>b) ? a : b ;
}


int main(){


    cout << ( my_max('y', 'x') == 'y') << '\n';  // type can be deduced here, no need to my_max<char>()




    return 0;
}