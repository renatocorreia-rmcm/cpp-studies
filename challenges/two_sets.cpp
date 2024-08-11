#include <iostream>

using namespace std;

int main(){

    int n;
    cin >> n;

    if ( n%4==0){
        cout << "YES" << endl;

        cout << n/2 << endl;
        for (int i = 0; i<n/4; i++){  // starts from 0 and walks 1/4
            cout << i+1 << " " << n-i << " ";
        }

        cout << endl << n/2 << endl;
        for (int i = n/4; i<n/2; i++){  // starts from 1/4 and walks 1/2
            cout << i+1 << " " << n-i << " ";
        }
    }

    else if ((n+1)%4==0 ){
        cout << "YES" << endl;

        cout << (n-1)/2 << endl;
        cout << n << " ";
        for (int i = 0; i<(n-1)/4; i++){
            cout << i+1 << " " << n-(i+1) << " ";
        }

        cout << endl << (n+1)/2 << endl;
        for (int i = (n-1)/4; i<(n-1)/2; i++){
            cout << i+1 << " " << n-(i+1) << " ";
        }
    }

    else {
        cout << "NO" << endl;
    }
    

    return 0;
}