//void pointer cant be dereferenced directly

#include <iostream>
using namespace std;

void print(void* ptr, char type){  //void pointer will be casted into passed datatype
    switch (type)
    {
    case 'c':
        cout<<*((char*)ptr)<<endl;  //(char*)ptr casts it, then *((char*)ptr) dereference it
        break;
    case 'i':
        cout<<*((int*)ptr)<<endl;
        break;
    }
}

int main(){
    int x = 5;
    char l = 'a';

    print(&x, 'i');
    print(&l, 'c');

    print(&x, 'c');  //in this situation compiler cant catch the error, because you can store any datatype in a void pointer, so you wont get an compile-time error

    return 0;
}