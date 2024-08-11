#include <iostream>

using namespace std;


int max_integer(int sequence[], int size);


int main(){

    int sequence[] = {-1, 0, 3, 2};
    int size = sizeof(sequence)/sizeof(int);

    cout << max_integer(sequence, size) << endl;



    return 0;
}


int max_integer(int sequence[], int size){

    int r = sequence[0];

    for (int i = 1; i<size; i++){
        if (sequence[i]>r){
            r = sequence[i];
        }
    }

    return r;
}