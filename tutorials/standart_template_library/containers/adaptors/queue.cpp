#include <iostream>

#include <queue>

using namespace std;

int main(){

    queue<int> q;
    for (int n: {1,2,3,4}){q.push(n);}

    cout<<q.size()<<endl;

    cout<<q.back()<<endl;

    while(!q.empty()){
        cout<<q.front()<<" ";
        q.pop();
    }
    cout << endl;

    cout<<q.size()<<endl;

    return 0;
}