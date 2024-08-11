#include <iostream>

class Worker {
    public:

    std::string name;
    std::string company;
    int age;

    Worker(std::string name, std::string company, int age){
        this->name = name;
        this->company = company;
        this->age = age;
    }

    void introduce(){
        std::cout << "name: " << name << std::endl;
        std::cout << "company: " << company << std::endl;
        std::cout << "age: " << age << std::endl;
    }
};

class Employee : public Worker {  //public inheritance allow access to parent class attributes  //default inheritance is private (still can create getters and setter on child to access parent)
    public:

    int depressionStage;
    Employee(std::string name, std::string company, int age, int depressionStage):Worker(name, company, age){
        this->depressionStage = depressionStage;
    }
};

int main() {

    Employee employee1("juan", "mcdon", 14, 2);
    employee1.introduce();
    
    return 0;
}