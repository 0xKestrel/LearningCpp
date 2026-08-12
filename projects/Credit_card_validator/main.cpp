#include<iostream>
#include <string>
#include<cmath>

int main (){
    std::string cc_no ;
    std::cout << "Please enter a credit card number: ";
    std::cin>> cc_no ;

                   int r {0},s{0}; 
            //sum of every second digit from right times 2
        for (int i = cc_no.length()-2; i >=0 ; i-=2)
        {   r =  ((cc_no[i]-'0')*2);
            s +=  (r% 10)     +   (std::floor(r/10));
        }        //unit digit    tens digit
        
                //sum of rest of the digits.
        for (int i = cc_no.length()-1; i >=0 ; i-=2)
        {s +=  (cc_no[i]-'0') ; }

    if (s%10==0)
            {std::cout<<"credit card number "<<cc_no<<" VALID!"; } 
    else    {std::cout<<"credit card number "<<cc_no<<" INVALID!";}       
}