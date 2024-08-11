#include <iostream>

//struct: structure that group related variables of many datatypes under one name
//the variables inside it are know as members and are accessed with the Class Member Access Operator "."

struct dog{
    std::string name;
    std::string color;
    double age;
    double size;
    char petClass;
};

void paintDog(dog &dog, std::string color);

int main(){
    dog dog1;
    dog1.name = "pipous";
    dog1.color = "wheat";
    dog1.age = 4.2;
    dog1.size = 0.1;
    dog1.petClass = 'B';

    dog dog2;
    dog2.name = "bird";
    dog2.color = "blue";
    dog2.age = 2;
    dog2.size = 0.2;
    dog2.petClass = 'D';

    paintDog(dog1, "light green");

    std::cout << dog1.color << "\n";
    std::cout << dog2.size << "\n";

    return 0;
}

void paintDog(dog &dog, std::string color){
    dog.color = color;
}