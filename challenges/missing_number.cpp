#include <iostream>

using namespace std;

int main (){

    double num;
    cin >> num;

    double sum = ((1 + num) * num) / 2;

    double temp;

    for (int i = 1; i < num; i++){
            cin >> temp;
            sum -= temp;
        }

    cout<<sum;

    return 0;
}
