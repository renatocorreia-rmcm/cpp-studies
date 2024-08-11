#include <iostream>


class Employee {  //class members: attributes and behaviors
    //private: default when not specified - not accessible outside class
    //protected: only derived classes can access (linke inherits)
    public: //accessible outside class
    std::string name;
    std::string company;
    int age;

    void introduce(){
        std::cout << "name: " << name << std::endl;
        std::cout << "company: " << company << std::endl;
        std::cout << "age: " << age << std::endl;
    }

    void hire(std::string comp){
        company = comp;
    }
};

int main() {

    Employee employee1;  //default constructor

    employee1.name = "juan";  //wouldnt work without public declaration
    employee1.hire("MCDon");

    employee1.introduce();

    return 0;
}
