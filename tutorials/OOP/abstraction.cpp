#include <iostream>

class AbstractWorker {  //is abstract because contains a pure virtual function
    virtual void haveFun()=0;  //a pure virtual function (abstract function) has his implementation obligatory  //to make a virtual function pure virtual, equal it to 0
};

class Employee : AbstractWorker {
    public:

    std::string name;
    std::string company;
    int age;

    Employee(std::string name, std::string company, int age){
        this->name = name;
        this->company = company;
        this->age = age;
    }

    void introduce(){
        std::cout << "name: " << name << std::endl;
        std::cout << "company: " << company << std::endl;
        std::cout << "age: " << age << std::endl;
    }
    
    void haveFun(){  // not inserting this would throw "object of abstract class type "Employee" is not allowed "
        std::cout<<name<<" is eating paper clips "<<std::endl;
    }
};

int main() {
    Employee employee1 = Employee("juan", "mcdon", 14);
    employee1.haveFun();
    
    return 0;
}