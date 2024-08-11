#include <iostream>
 
using namespace std;

int main() {
 
    int r = 6;
    int buffer;

    for (int i = 0; i<3; i++){
        cin >> buffer;
        r-=buffer;
    }

    cout<<r<<endl;
 
    return 0;
}