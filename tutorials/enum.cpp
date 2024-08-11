#include <iostream>

//enums: user-defined data type that consists of paired named-integer constants. GREAT if you have a set of potential options

enum Day {sunday = 1, monday = 2, tuesday = 3, wednesday = 4, thursday = 5, friday = 6, saturday = 7};  //if numerical values hadnt been assigned, default would be items indexes

int main () {
    Day today = monday;  //or Day today = 0

    switch(today){
        case 1:
        case 7:
            std::cout<<"go surf"<<"\n";
            break;        
        case 2:     
        case 3:      
        case 4:     
        case 5:
            std::cout<<"no surf?"<<"\n";
            break;        
        case 6:
            std::cout<<"drop college shit, go surf"<<"\n";
            break;
    }

    return 0;
}