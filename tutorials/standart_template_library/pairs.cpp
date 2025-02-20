#include <iostream>

#include <utility>  //some other includes, as <map>, automatically includes <utility>

using namespace std;

// pairs hold exactly two elements of possibly different types
// std::pair<T1, T2> myPair;  // declaration
// std::pair<T1, T2> myPair(x, y);  //initialization

int main(){

    pair<char, float> p1('b',1.618);  // initializing
    cout<<p1.first<<endl;
    cout<<p1.second<<endl;

    pair<string, int> p2;  // declarating
    p2.first = "mb";
    p2.second = 10;
    cout<<p2.first<<" "<<p2.second<<endl;

    p2.second = 11;  // changing values
    cout<<p2.second<<endl;

    cout<<pair<float, float>(1.1,1.21).first<<endl;  // "anonymous"
    cout<<make_pair(3, "three").first; // make_pair() is often used to insert elements into containers more conveniently  //types are inferred
    //class template does not inferr parameter types, function template does.


    return 0;
}