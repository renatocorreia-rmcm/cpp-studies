#include <iostream>

using namespace std;


int busca_linear(int sequence[], int size, int x);


int main(){

    int sequence[] = {-1, 0, 3, 2};
    int size = sizeof(sequence)/sizeof(int);

    cout << busca_linear(sequence, size, 9) << endl;
    cout << busca_linear(sequence, size, 3) << endl;

    return 0;
}


int busca_linear(int sequence[], int size, int x){

    for (int i = 0; i<size; i++){
        if (sequence[i] == x){
            return i;
        }
    }

    return -1;
    
}