#include<iostream>
#include<cmath>

void ask2num (long double &a,long double &b)
{    while (true)
    {   std::cout << "Enter the first number: " ;
            std::cin >> a ;
        if (std::cin.fail())
        {   std::cout << "Invalid input! Please enter a numeric value.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); break;}  
    }
    while (true)
    {   std::cout << "Enter the Second number: " ;
            std::cin >> b ;
         if (std::cin.fail())
        {   std::cout << "Invalid input! Please enter a numeric value.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); break;}  
    }  
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
    long double num1, num2, res;

    std::cout << "-------------------------------------- CALCULATOR -------------------------------------- \n" ;

        //----------Type of Calculator----------
       do
        {   std::cout << "Please Choose the type of Calculator (A or B): ";
            std::cin >> type;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (!validate_Type (type))
                {
                    std::cout << "The Entered type of Calculator is Invalid! \n Try again! \n \n";
                }
        }while(!validate_Type (type));
            
        //----------Choose the Opperator----------
        do
        {   std::cout << "Enter the opperation to be done (Enter only +,-,*,/,%): "  ;
            std::cin >> op ;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (!validate_op (op))
                {
                   std::cout << "The Entered Opperation is Invalid! \n Try again! \n \n";
                }
        } while (!validate_op(op));
    
        ask2num(num1,num2);

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
         
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx \n" ;
}