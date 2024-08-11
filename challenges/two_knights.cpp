#include <iostream>
using namespace std;

// permutação com repetição para total de posicionamentos
    // P^(k^2-2),2 (k^2)  =  k^2*(k^2-1)/2
// permutação de retangulos 2x3 para total de posições atacantes

int main(){

    long k;
    cin >> k;

    cout << 0 << endl;

    long total_positions;
    long atack_positions;

    if (k>=2){
        total_positions = 2*2*(2*2-1)/2;
        atack_positions = 0;
        cout << total_positions-atack_positions << endl;
    }

    for (long i = 3; i <= k; i++){

        total_positions = i*i*(i*i-1)/2;
        atack_positions = (i-2)*(i-1)*2*2;  //*2 for turn x and y axis and *2 for w atack b and b atack w

        cout << total_positions-atack_positions << endl;
    }
    return 0;
}
