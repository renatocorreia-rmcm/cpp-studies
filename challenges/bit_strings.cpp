#include <iostream>
#include <cmath>

using namespace std;

// int max size  : 2,147,483,647

int main(){

    int n;
    cin >> n;
    int m = 1000000007;
    // print 2^n mod m

    // integer leaks on 2^31 (keep 30)

    // n = d*30 + r
    int d = floor(n/30.0);
    int r = n%30;

    int result = 1;

    for (int i = 0; i<d; i++){
        
    }

    return 0;
}