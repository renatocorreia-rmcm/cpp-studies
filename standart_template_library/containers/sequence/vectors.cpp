#include <iostream>

#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>
#include <bits/stdc++.h>


using namespace std;


int main(){

    vector<int> v;
    v.push_back(20);
    v.push_back(12);
    v.push_back(400);
    cout << v.size() << endl;

    //vector elements can be randonly accessed

    cout<<v[2]<<endl;  //no range check
    cout<<v.at(2)<<endl;  //can throw range_error exception

    //because of the random access, a vector can be navigated like an native array
    for (int i = 0; i<v.size(); i++){
        cout<<v[i]<<endl;
    }
    //but, through an iterator, it is faster and universal for all containers 
    for (vector<int>::iterator itr = v.begin(); itr!=v.end(); itr++){  //so vector<int>::... could be replaced by list<int>::..., for example
        cout<<*itr<<endl;
    }
    //new c++11 way to cross a container
    for(int element: v){  // is equivalent to: for (auto it = vec.begin(); it != vec.end(); ++it)
        cout<<element<<endl;
    }

    return 0;
}