#include <iostream>

int main(){
    //LOGICAL OPERATORS
    std::cout << (!true) << (true&&false) << (true||false) << "\n";

    //IF
    bool surfing = false;
    if (!surfing){
        std::cout << "go surf" << "\n";
    }
    else if (surfing){
       std::cout << "nice" << "\n";
    }
    
    //TERNARY OPERATOR;
    std::cout << (surfing?"nice":"go surf") << "\n";

    //SWITCH
    int weekday = 5;
    std::string weekdayName;
    switch (weekday)
    {
    case 1:
        weekdayName = "domingo";
        break;
    case 2:
        weekdayName = "segunda-feira";
        break;
    case 3:
        weekdayName = "terça-feira";
        break;
    case 4:
        weekdayName = "quarta-feira";
        break;
    case 5:
        weekdayName = "quinta-feira";
        break;
    case 6:
        weekdayName = "sexta-feira";
        break;
    case 7:
        weekdayName = "sábado";
        break;
    default:
        weekdayName = "wtf go to mars";
        break;
    }
    std::cout << weekdayName << "\n";

    //WHILE
    bool b = false;
    while (b)
    {
        std::cout << "set a bool for the while loop" << "\n";
        std::cin >> b;
    }
    
    do {
        std::cout << "b: " << b << "\n";
    } while(b);

    //FOR
    for (int index = 0; index<=12; index+=4){
        std::cout << index << "\n";
    }

    //LOOPING KEYWORDS
        //break - exit loop
        //continue - skips to next iteration
    for (int c = 0; c<=10; c++){
        if(c==5){
            continue;
        }
        else if (c==7)
        {
            break;
        }
        std::cout << c << "\n";

    }

    return 0;
}