#include <iostream>

#include <vector>
#include <iterator>
#include <algorithm>
//#include <bits/stdc++.h>  // bits : generic librarie collection  // stdc++ : standart librarie c++  // so this header call all those others headers

using namespace std;  // StandartTemplateLibrarie is inside STD so everything inside STL library is defined inside STD namespace


//vector: dinamic array that can grow
    //it is dynamically alocated on the heap

int main(){

    vector<int> myVec;

    myVec.push_back(12);  // appends an element to the end of the array
    myVec.push_back(144);
    myVec.push_back(3);

    //each container provide an iterate interface
    vector<int>::iterator firstItr = myVec.begin();  //return the iterator that points to the first element of the vector
    vector<int>::iterator lastItr = myVec.end();  // half open: [begin, end[

    for (vector<int>::iterator itr = firstItr; itr!=lastItr; itr++){
        cout<< *itr << " ";  // iterator is a class, but it behaves just like a regular pointer
    }
    cout << endl;

    // *vec.end(): undefined behavior: danger

    sort(firstItr, lastItr);  // algorithms do not operate on containers directly, but on iterators
    for (vector<int>::iterator itr = firstItr; itr!=lastItr; itr++){
        cout<< *itr << " ";  // iterator is a class, but it behaves just like a regular pointer
    }
    cout << endl;


    return 0;
}