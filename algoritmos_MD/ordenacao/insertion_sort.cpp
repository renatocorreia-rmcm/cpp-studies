#include <iostream>
#include <vector>

// expensive in terms of time because got to realocate all vector

using namespace std;

vector<int> insertion_sort(vector<int> sequence, int size);

int main(){


    vector<int> sequence = {10, 9, 8, 7, 6, 5};
    int size = sequence.size();

    vector<int> sorted = insertion_sort(sequence, size);

    for (int i: sorted){
        cout<< i << " ";
    }
    cout << endl;

    return 0;
}

vector<int> insertion_sort(vector<int> sequence, int size){

    for (int i_carried = 0; i_carried<size; i_carried++){
        for (int i_compared = 0; i_compared<i_carried; i_compared++){
            if (sequence.at(i_carried) <= sequence.at(i_compared)){
                sequence.insert(sequence.begin()+i_compared, sequence.at(i_carried));
                sequence.erase(sequence.begin()+i_carried+1);
                break;
            }
        }
    }

    return sequence;
}