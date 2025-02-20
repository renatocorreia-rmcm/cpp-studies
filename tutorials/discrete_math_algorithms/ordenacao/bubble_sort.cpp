#include <iostream>

using namespace std;


int* recursive_bubblesort(int sequence[], int size);

int* iterative_bubblesort(int sequence[], int size);


int main(){

    //int sequence[] = {1, 5, 6, 0, 10, -7, 4};
    int sequence[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2};
    int size = sizeof(sequence)/sizeof(int);


    int sequence_copy[size];
    copy(sequence, sequence+size, sequence_copy);

    int* recursive_sorted_sequence = recursive_bubblesort(sequence_copy, size);
    
    for (int i = 0; i < size; i++) cout << recursive_sorted_sequence[i] << " ";
    cout << endl;


    copy(sequence, sequence+size, sequence_copy);

    int* iterative_sorted_sequence = iterative_bubblesort(sequence_copy, size);

    for (int i = 0; i < size; i++) cout << iterative_sorted_sequence[i] << " ";
    cout << endl;

    
    return 0;
}


int* recursive_bubblesort(int sequence[], int size){
    bool finished = true;
    
    for (int index = 0; index < size-1; index++)
    {
        if (sequence[index]>sequence[index+1])
        {   
            finished = false;

            int temp = sequence[index];

            sequence[index] = sequence[index+1];
            sequence[index+1] = temp;
        }
    }

    return finished ? sequence : recursive_bubblesort(sequence, size);

}

int* iterative_bubblesort(int sequence[], int size){
    
    for (int iteration = 0; iteration<size-1; iteration++){

        for (int index = 0; index < size-1; index++)
        {
            if (sequence[index]>sequence[index+1])
            {   
                int temp = sequence[index];
                sequence[index] = sequence[index+1];
                sequence[index+1] = temp;
            }
        }

    }

    return sequence;

}
