#include <iostream>

#include <map>
#include <iterator>


using namespace std;

int main(){

    map<char, int> m;

    m.insert(pair<char, int>('s', 10));

    m.insert(make_pair('r', 9));
    m.insert(make_pair('t',8));

    map<char, int>::iterator itr = m.find('s');

    for (map<char, int>::iterator it = m.begin(); it!=m.end(); it++){
        cout<<(*it).first<<" -> "<<(*it).second<<endl;
    }

    return 0;
}