#include <iostream>

int main(){
    std::string languages[] = {"python", "java", "js", "c#", "c++"};

    std::cout << languages << "\n";
    std::cout << languages[0] << "\n";

    languages[3] = "microsoft's java";
    std::cout << languages[3] << "\n";

    std::string systems[3];

    systems[0]="windows";
    systems[1]="linux";
    systems[2]="mac";

    int languagesLen = sizeof(languages)/sizeof(std::string);
    std::cout << languagesLen << " programming languages" << "\n";

    for (int i = 0; i<languagesLen; i++){  //i<=languagesLen; would reach 1 more than languagesLen
        std::cout << i << " - " << languages[i] << "\n";
    }

    for(std::string l : languages){  //for each
        std::cout << "-> " << l << "\n";
    }

    int array2d[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};  //[rows][columns]

    return 0;
}
