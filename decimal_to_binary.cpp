#include <iostream>
#include <cmath>

using namespace std;

/*
may create a function
pass d by reference, no need to another variables
how to assign it to a integer instead of printing?
*/

int main(){

    int d;
    cin >> d;

    int bits = floor(log(d)/log(2));  // amount of bits
    int copy;

    for (int i = 0; i<=bits; i++){
        copy = floor(d/(1<<(bits-i)));  // d / (2^(bits-i))
        cout << copy%2;
    }cout<<endl;
    
    return 0;
}
