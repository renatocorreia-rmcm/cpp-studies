#include <iostream>


class Employee {

    private:

    std::string name;
    std::string company;
    int age;

    public:

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

    void hire(std::string comp){
        company = comp;
    }

    std::string getName(){  //getter
        return name;
    }
    void setName(std::string n){  //setter
        if (n!="dionathas"){
            name = n;
        }
        else {
            throw "nome feio da porra doido";  //name could just not be updated instead
        }
    }
};

int main() {
    Employee employee1 = Employee("juan", "mcdon", 14);

    //std::cout << employee1.name << std::endl;  //error
    //employee1.name = "jorge";  //error

    employee1.setName("jorje");
    employee1.setName("dionathas");  //error
    std::cout<< employee1.getName()<<std::endl;


    return 0;
}