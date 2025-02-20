#include <iostream>
using namespace std;


int main(){

    int lucky[] = {12,144,9,0};

    cout<<lucky<<endl;  //the name of the array will be the first element address
    cout<<&lucky[0]<<endl;  //so the given name (lucky) behaves like a pointer
    cout<<&lucky[0]<<endl;  //and the [0] behaves like a operator for dereferencing (*)
    cout<<&lucky[1]<<endl;
    cout<<&lucky[2]<<endl;  // so lucky can be seen as the first address, and here we add +2 addresses spaces
    //so these are equivalent
    cout<<lucky[2]<<endl;
    cout<<*(lucky+2)<<endl;
    //and thats why we can have this type of error
    //cout<<*(lucky+4)<<endl;  //BUT DONT DO IT!! ITS DANGEROUS


    int nums[5];

    for (int i=0; i<5; i++){
        cout<<i<<"num: ";
        cin>>nums[i];
    }


    return 0;
}