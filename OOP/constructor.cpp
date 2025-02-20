#include <iostream>


class Employee {
    public:
    std::string name;
    std::string company;
    int age;

    //constructor: special method invoked when a object is created
    Employee(std::string name, std::string company, int age){  //defined constructor  //no return type, same name than class, must be public
        //  you typically use the -> operator in C++ when you're working with pointers to access members of objects  //no need to use if there no name colision with global scope
        this->name = name;  //  this is a pointer to the current object instance  
        this->company = company;
        this->age = age;

    }

    void introduce(){
        std::cout << "name: " << name << std::endl;
        std::cout << "company: " << company << std::endl;
        std::cout << "age: " << age << std::endl;
    }
};

int main() {
    Employee employee1 = Employee("juan", "mcdon", 14);
    Employee employee2("carlos", "bobs", 41);

    employee1.introduce();
    employee2.introduce();
    
    return 0;
}