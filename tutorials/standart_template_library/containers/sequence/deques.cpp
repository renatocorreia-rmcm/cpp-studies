#include <iostream>

#include <deque>

using namespace std;

int main(){

    deque<int> d = {1, 2};

    d.push_back(3);
    d.push_front(0);

    for (int i:d){
        cout<<i<<" ";
    }
    cout<<endl;

    cout<<d[1]<<" "<<d.at(d.size()-1)<<endl;

    return 0;
}