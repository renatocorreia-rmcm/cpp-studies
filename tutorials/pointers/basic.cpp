//pointer = variable that holds an address

#include <iostream>
using namespace std;

int main(){
    int n = 5;
    cout<<n<<endl;
    cout<<&n<<endl;

    int* p = &n;  //pointer must have same datatype than pointed
    cout<<p<<endl;
    cout<<*p<<endl;  //dereferencing

    *p = 10;
    cout<<p<<endl;
    cout<<*p<<endl;
    cout<<n<<endl;

    return 0;
}
