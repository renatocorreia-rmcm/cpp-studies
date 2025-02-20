#include <iostream>

#include <list>
#include <algorithm>


using namespace std;

int main(){

    list<int> l = {5, 2, 9};
     
    l.push_back(6);
    l.push_front(4);
    
    list<int>::iterator itr = find(l.begin(), l.end(), 2);  // itr->2  //(itr points to 2)
    cout<<*itr<<endl;

    l.insert(itr, 8);  //dont replace, but push elements above forward
    for (int i: l) {cout<<i<<" ";} cout<<endl;
    l.erase(itr);  //now its "replaced"
    for (int i: l) {cout<<i<<" ";} cout<<endl;

    list<int> l2;
    l2.splice(l2.begin(), l,find(l.begin(), l.end(), 5), find(l.begin(), l.end(), 9));  //(local to insert(iterator), list to cut, start(iterator), end(iterator))
    
    for (int i: l2) {cout<<i<<" ";} cout<<endl; 
    for (int i: l) {cout<<i<<" ";} cout<<endl;


    return 0;
}