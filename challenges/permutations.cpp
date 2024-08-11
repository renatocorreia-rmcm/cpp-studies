#include <iostream>

using namespace std;

int main(){
    long n;
    cin >> n;

    if (n==3 or n==2){
        cout<<"NO SOLUTION";
    }
    else{
        for(long i = n-1; i>0; i-=2){  //even
            cout<<i<<" ";
        }
        for (long i = n; i>0; i-=2){  // odd
            cout<<i<<" ";
        }
    }


    return 0;
}