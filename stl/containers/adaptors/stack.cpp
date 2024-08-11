#include <iostream>

#include <stack>

using namespace std;


int main(){

    stack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    //for (int n: {1,2,3,4}){s.push(n);}

    s.pop();

    while(!s.empty()){
        cout<<s.top()<<" ";
        s.pop();
    }
    cout<<endl;

    cout<<s.size()<<endl;
    //cout<<s.top()<<endl;//throw error if stack is empty
    cout<<s.empty()<<endl;
    

    return 0;
}