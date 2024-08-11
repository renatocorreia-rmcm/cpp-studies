#include <iostream>

//pointer: variable that stores a memory adress of another variable
//& adress of operator
//* dereference operator  //dereferencing: accessing the value that is pointed by a pointer variable - essentially asking the compiler to retrieve the value stored at the memory address held by the pointer

int main(){
    std::string name = "juan";
    std::string *ptrName = &name;
    std::cout << ptrName << "\n";
    std::cout << *ptrName << "\n";

    int num = 12;
    int *ptrNum = &num;
    std::cout << ptrNum << "\n";
    std::cout << *ptrNum << "\n";

    std::string pizzas[3] = {"pepperoni pizza","cheese pizza","strogonoff pizza"};
    //std::string *ptrPizzas = &pizzas;  //error because an array is already an adress - no nedd to use & adress of operator
    std::string *ptrPizzas = pizzas;
    std::cout << pizzas << "\n";
    std::cout << ptrPizzas << "\n";
    std::cout << *ptrPizzas << "\n";


    //NULL POINTERS

    //null: special value that means no value
    //when a pointer is null, it is not pointing at anything
    //nullptr keyword represents a null pointer literal - helpful when determining if an address was assigned to a pointer

    //int *pointer;
    /*
    If a pointer is not initialized, it is left pointing to some arbitrary memory location,
    and dereferencing it can lead to undefined behavior as crashing the program, accessing unintended data, or other unexpected behavior.
    */
    int *pointer = nullptr;  //or int *pointer = NULL;
    //Initializing a pointer with a null value is a defensive programming practice.
    //std::cout << pointer << "\n";
    //std::cout << *pointer<< "\n";
    /*
    It ensures that if the pointer is accidentally dereferenced before it's properly assigned a valid memory address, it will not access any unintended or invalid memory location,
    but likely result in a more predictable behavior, such as a segmentation fault or a null pointer dereference error, which can be easier to diagnose and debug compared to accessing arbitrary memory locations.
    */
    int x = 12;
    pointer = &x;
    std::cout << pointer << "\n";
    std::cout << *pointer<< "\n";
    

    return 0;
}