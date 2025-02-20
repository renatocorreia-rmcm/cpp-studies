#include <iostream>

#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

int main(){

    set<int> s;
    
    s.insert({1,7});
    s.insert(3);
    s.insert(0);

    for(int i: s){cout<<i<<" ";} cout<<endl;

    set<int>::iterator itr;
    itr = s.find(3);

    pair<set<int>::iterator, bool> r;
    r = s.insert(3);
    cout<<r.second<<endl;

    s.erase(3);
    for(int i: s){cout<<i<<" ";} cout<<endl;

    return 0;
}