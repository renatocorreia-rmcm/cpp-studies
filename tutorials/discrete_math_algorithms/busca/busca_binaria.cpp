// requer lista em ordem crescente

#include <iostream>

using namespace std;


int busca_binaria(int* sequence, int original_size, int x, int start=0, int end=-1);


int main(){

    int sequence[] = {1,2,4,5,6,7,8,9,10,11,13,14,15,16,18};  // no 3, 12, 17
    int size = sizeof(sequence)/sizeof(int);

    //random
    cout << busca_binaria(sequence, size, 4, 0, -1) << endl;
    cout << busca_binaria(sequence, size, 9, 0, -1) << endl;

    //edges
    cout << busca_binaria(sequence, size, 1, 0, -1) << endl;
    cout << busca_binaria(sequence, size, 18, 0, -1) << endl;

    // not in array
    cout << busca_binaria(sequence, size, 3, 0, -1) << endl;
    cout << busca_binaria(sequence, size, 12, 0, -1) << endl;

    // outside range
    cout << busca_binaria(sequence, size, 20, 0, -1) << endl;
    cout << busca_binaria(sequence, size, -5, 0, -1) << endl;

    return 0;
}

int busca_binaria(int* sequence, int original_size, int x, int start, int end){
    
    if (end<0) end+=original_size;
    
    int current_size = end-start+1;
    int middle_index = (end+start)/2;

    if (x==sequence[middle_index]){
        return middle_index;
    }

    else if (current_size==1){
        return -1;
    }

    else if (x<sequence[middle_index]){
        return busca_binaria(sequence, original_size, x, start, middle_index);
    }

    else if (x>sequence[middle_index]){
        return busca_binaria(sequence, original_size, x, middle_index+1, end);
    }

    return -1;
}