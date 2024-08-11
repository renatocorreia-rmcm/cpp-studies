#include <iostream>

int main(){
    int nums[] = {1, 5, 6, 8, 2, 0, 7, 3, 9, 4};
    int len = sizeof(nums)/sizeof(int);

    bool finished;
    int temp;

    do {
        finished = true;
        for (int a = 0; a<len-1; a++){
            if (nums[a]>nums[a+1]){
                temp = nums[a];
                nums[a] = nums[a+1];
                nums[a+1] = temp;
                finished = false;
            }
        }
    } while(!finished);

    return 0;
}
