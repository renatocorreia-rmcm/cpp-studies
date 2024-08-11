#include <iostream>

using namespace std;

int main(){

    long tests;
    cin>>tests;

    long y;
    long x;
    long corner;
    bool corner_is_odd;

    for (long c = 0; c<tests; c++){
        cin >> y;
        cin >> x;
        corner = (x>y?x:y);
        corner_is_odd = (corner%2==0?false:true);

        if (corner_is_odd){
            cout << corner*corner-(corner-1)+(x-y) << endl;
        }
        else {
            cout << corner*corner-(corner-1)-(x-y) << endl;
        }
    }
    return 0;
}