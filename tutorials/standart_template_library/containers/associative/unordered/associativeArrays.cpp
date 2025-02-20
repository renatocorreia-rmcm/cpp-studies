#include <iostream>

#include <map>
#include <unordered_map>

using namespace std;

//ignore this for now
void foo(const unordered_map<char, string> &m){
    //m['t'] = "thursday";  //compile error, const is not modifiable
    //cout << m['t'] << endl  //compile error, subscript operator provide write operation to the container, so compiler assumes you gonna write on it
    auto itr = m.find('t');
    if (itr != m.end()){
        cout << (*itr).first << " " << itr->second << endl;  //just different maners to access itr pointeds by
    }   
}


int main(){

    unordered_map<char, string> um = {{'s', "sunday"}, {'m', "monday"}};

    cout<<um['s']<<endl;  //no range check
    cout<<um.at('s')<<endl;  //range check

    um['t'] = "tuesday";  // insert item  //this and the following would throw an error in an ordered container (as vec[4]=x in an lenght 4 vec)
    um.insert(make_pair('f', "friday"));

    //um.insert(make_pair('m', "MONDAY"))  //error: its not a multimap, cant have two items with the same key
    um['m'] = "MONDAY";  //"m" key value has been modifyed  //A[x] = SUBSCRIPT OPERATOR  //it provides write access to the operator

    for (auto p : um) {cout << p.second << " ";}
    cout << endl;

    //see foo above header
    foo(um);

    return 0;
}