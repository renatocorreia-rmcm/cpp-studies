#include <iostream>
#include <cmath>
 
using namespace std;
 
int main() {
 
    int num;
    cin >> num;
    int r = 0;
 
    int max_pow = log(num)/log(5);

    for (int p = 1; p<=max_pow; p++){
        r += floor(num/pow(5, p));
    }

    cout << r;
 
    return 0;
}