#include<iostream>
#include<cmath>

void ask2num (long double &a,long double &b){
    std::cout << "Enter the first number: " ;
            std::cin >> a ;
    std::cout << "Enter the Second number: " ;
            std::cin >> b ;
}

bool validate_op(char &a){
    return (a=='+'|| a=='-'|| a=='*'|| a=='/'|| a=='%');
}

int main (){

    char op ;
    long double num1, num2;

    std::cout << "-------------------------------------- CALCULATOR -------------------------------------- \n" ;
        

        do{
            std::cout << "Enter the opperation to be done (Enter only +,-,*,/,%): "  ;
            std::cin >> op ;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (not(validate_op (op))){
                   std::cout << "The Entered Opperation is Invalid! \n Try again \n \n";
                }
        } while (not (validate_op(op)));
    
        ask2num(num1,num2);
                
        switch (op){
            case '+':
                std::cout << "The sum of the Numbers " << num1 << " and " << num2 << " is " << num1+num2 << '\n'; 
            break;

            case '-':
                std::cout << "The difference of the Numbers " << num1 << " and " << num2 << " is " << num1-num2 << '\n'; 
            break;    
        
            case '*':
                std::cout << "The product of the Numbers " << num1 << " and " << num2 << " is " << num1*num2 << '\n'; 
            break;  

            case '/':
                std::cout << "The quotient of the Numbers " << num1 << " and " << num2 << " is " << num1/num2 << '\n'; 
            break;

            case '%':
                std::cout << "The Modulo/Remainder of the Numbers " << num1 << " and " << num2 << " is " << std::fmod(num1, num2)
                                                                                                                        << '\n'; 
            break;    
        }
            
        



    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx \n" ;

    
}