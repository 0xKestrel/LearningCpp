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

bool validate_Type(char &a){
    return (a=='A'|| a=='a'|| a=='B'|| a=='b');
}

int main (){

    char op ;
    char type;
    long double num1, num2;

    std::cout << "-------------------------------------- CALCULATOR -------------------------------------- \n" ;

                // Type of Calculator
       do{
            std::cout << "Please Choose the type of Calculator (A or B): ";
            std::cin >> type;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (not(validate_Type (type)))
                {
                    std::cout << "The Entered type of Calculator is Invalid! \n Try again! \n \n";
                }
        }while(not(validate_Type (type)));
            
                // Choose the Opperator
        do{
            std::cout << "Enter the opperation to be done (Enter only +,-,*,/,%): "  ;
            std::cin >> op ;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (not(validate_op (op)))
                {
                   std::cout << "The Entered Opperation is Invalid! \n Try again! \n \n";
                }
        } while (not (validate_op(op)));
    
        ask2num(num1,num2);

                // Type A Caculator
        if (type =='A'||type == 'a')
        {            
            switch (op)
            {
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
                    std::cout << "The Modulo/Remainder of the Numbers " << num1 << " and " << num2 << " is " 
                                                                                        << std::fmod(num1, num2) << '\n'; 
                break;  
            }                               // Type B Calculator
        } else if(type =='B'||type =='b') 
        {   switch (op)
            {
                case '+':
                    std::cout << num1 << " + " << num2 << " = " << num1+num2 << '\n'; 
                break;

                case '-':
                    std::cout << num1 << " - " << num2 << " = " << num1-num2 << '\n'; 
               break;    
        
                case '*':
                    std::cout << num1 << " * " << num2 << " = " << num1*num2 << '\n'; 
                break;  

                case '/':
                    std::cout << num1 << " / " << num2 << " = " << num1/num2 << '\n'; 
                break;

                case '%':
                    std::cout << num1 << " mod " << num2 << " = " << std::fmod(num1, num2) << '\n'; 
                break;
            }
        } 
        
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx \n" ;  
}