#include <iostream>

using namespace std;

int main(){

    long n;
    cin >> n;

    long moves = 0;
    long current;
    long load;
    cin >> load;

    for (long i = 1; i<n; i++){
        cin>>current;
        if (current<load){
            moves+=(load-current);
        }
        else {
            load = current;
        }
    }

    cout << moves << endl;

    return 0;
}