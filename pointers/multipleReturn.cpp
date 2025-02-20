#include <iostream>
using namespace std;


void GetMinMax(int arr[], int len, int* min, int* max){
    for (int i = 1; i<len; i++){
        if (arr[i]>*max){
            *max = arr[i];
        }
        else if (arr[i]<*min){
            *min = arr[i];
        }
    }
}


int main() {
    int numbers [5] = { 5,4,-2,29,6 };
    int len = sizeof(numbers)/sizeof(int);  // or /sizeof(numbers[0])

    int min = numbers[0];
    int max = numbers[0];

    GetMinMax(numbers, len, &min, &max);

    cout<<min<<endl;
    cout<<max<<endl;

    return 0;
}
