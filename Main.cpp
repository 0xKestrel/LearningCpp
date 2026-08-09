#include<iostream>
#include<cmath>

int main (){

    char op ;
    double num1 ;
    double num2 ;
    double res  ;    

    std::cout << "-------------------------------------- CALCULATOR -------------------------------------- \n" ;
        std::cout << "Enter the opperation to be done (Enter only +,-,*,/,%): "  ;
            std::cin >> op ;
        std::cout << "Enter the first number: " ;
            std::cin >> num1 ;
        std::cout << "Enter the first number: " ;
            std::cin >> num2 ;

        switch (op)
        {
        case '+':
                std::cout << "The sum of the Numbers " << num1 << " and " << num2 << " is " << num1+num2 << '\n'; 
            break;
        
        default:
            break;
        }



    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx \n" ;

    
}