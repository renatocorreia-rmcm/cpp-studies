#include <iostream>

#include <unordered_set>
#include <vector>

using namespace std;

int main(){

    unordered_set<string> us = {"red", "green", "blue"};

    unordered_set<string>::iterator itr = us.find("green");  // O(1)
    if (itr!=us.end()){  // because if argument was not found, it will return us.end()
        cout<< *itr << endl;
    }

    us.insert("cyan");  // O(1)

    vector<string> v = {"magenta", "yellow", "white", "black"};
    us.insert(v.begin(), v.end());


    // order may seem random because it depends on the hash values of the elements and the internal structure of the set. 
    // However, when you print the set, it iterates through the elements in a consistent order
    for (string c: us){cout << c << " ";}  
    cout << endl;

    // the internal structure of the unordered set doesn't change between printings
    for (string c: us){cout << c << " ";}  
    cout << endl;


    // hash table specific APIs

    cout << "n elements / n buckets: " << us.load_factor() << endl;

    string x = "red";
    cout << x << "is in bucket#" << us.bucket(x) << endl;
    cout << "green" << "is in bucket " << us.bucket("green") << endl;

    cout << "total number of buckets " << us.bucket_count() << endl;
    

    return 0;
}