#include<iostream>
#include<cmath>
#include<limits>
#include<functional>

void ask_a_num (long double &a, const std::string &prompt_to_ask)
{    while (true)
    {   std::cout << prompt_to_ask ;
            std::cin >> a ;
        if (std::cin.fail()|| std::cin.peek() != '\n')
        {   std::cout << "Invalid input! Please enter a numeric value.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); break;}  
    }}
   

bool validate_op(char a){
    return (a=='+'|| a=='-'|| a=='*'|| a=='/'|| a=='%');}

bool validate_Type(char a){
    return (a=='A'|| a=='a'|| a=='B'|| a=='b');}

void input(char &a, const std::string &prompt_to_ask, const std::string &prompt_if_error, std::function<bool(char)> isValid  ){
    while(true)
    {   std::cout<< prompt_to_ask;
        std::cin>>a;
            if (!isValid(a)|| std::cin.peek() != '\n')
            {    std::cout << prompt_if_error;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {break;}
}   }

int main (){
        std::cout << "-------------------------------------- CALCULATOR -------------------------------------- \n" ;
        char choice{};

    do{
    char op, type;
    long double num1, num2, res;
        //----------Type of Calculator----------
       input(type, 
            "Please Choose the type of Calculator (A or B): ",
                "The Entered type of Calculator is Invalid! \n Try again! \n \n", 
                    validate_Type);
            
        //----------Choose the Opperator----------
       input(op, 
            "Enter the opperation to be done (Enter only +,-,*,/,%): ", 
                "The Entered Opperation is Invalid! \n Try again! \n \n", 
                    validate_op ) ;
    
        ask_a_num(num1, "Enter the first number: " );
        ask_a_num(num2, "Enter the Second number: " );

        bool cal_successful = 1;
        //----------Calculations----------
        switch (op)
        {
            case '+': res = num1 + num2 ; break;
            case '-': res = num1 - num2 ; break;
            case '*': res = num1 * num2 ; break;
            case '/':
                if (num2 == 0)
                {   std::cout << "Error: Division by zero is undefined!\n" ;
                     cal_successful = 0 ;
                } else { res = num1 / num2 ; }    
            break;
            case '%':
                if (num2 == 0)
                {   std::cout << "Error: Modulo by zero is undefined!\n" ;
                     cal_successful = 0 ;
                } else { res = std::fmod(num1, num2) ; }
            break ;            
        }

        if (cal_successful)
        {                                       //----------Type A Caculator's Output----------
            if (type =='A'||type == 'a')
            {    switch (op)
                {case '+': std::cout << "The sum of the Numbers " << num1 << " and " << num2 << " is " << res << '\n'; break;
                 case '-': std::cout << "The difference of the Numbers " << num1 << " and " << num2 << " is " << res << '\n'; break;
                 case '*': std::cout << "The product of the Numbers " << num1 << " and " << num2 << " is " << res << '\n'; break;
                 case '/': std::cout << "The quotient of the Numbers " << num1 << " and " << num2 << " is " << res << '\n'; break;
                 case '%': std::cout << "The Modulo/Remainder of the Numbers " << num1 << " and " << num2 << " is " << res << '\n'; break;  
                }                               //----------Type B Calculator's Output----------
            } else if(type =='B'||type =='b') 
            {   if (op == '%') {std::cout<< num1 << " " << "mod" << " " << num2 << " = " << res << '\n' ; } 
                else {std::cout<< num1 << " " << op << " " << num2 << " = " << res << '\n' ; }       
        }   }
    std::cout << "\nDo you want to perform another calculation? (y/n): ";
        std::cin >> choice;    
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');        
        } while (choice == 'y' || choice == 'Y');
        std::cout << "Exiting calculator. Goodbye!\n";     
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx \n" ;
return 0;    
}