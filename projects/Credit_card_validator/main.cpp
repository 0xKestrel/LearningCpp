#include<iostream>
#include <string>

bool in_num_val (std::string &num) {
    
   return num.length()>=13 && num.length()<=19;}

void in_num (std::string &num){
    do
    {   
        std::cout << "Enter a credit card number: ";
        std::cin>> num ;

        if(!in_num_val(num))
            {std::cout<<"\nThe entered number is invalid! A credit card number should be 13-19 digits long.\nTry again!\n\n";}

    } while ( !in_num_val(num) );
     
}

int main (){
    std::string cc_no;
    in_num(cc_no);

                   int r {0},s{0}; 
        //-------Sum of every second digit from right times 2-------
        for (int i = cc_no.length()-2; i >=0 ; i-=2)
        {   r = ((cc_no[i]-'0')*2);
            s += (r% 10)     +   (r/10);
        }        //unit digit    tens digit
        //-------Sum of rest of the digits.---------
        for (int i = cc_no.length()-1; i >=0 ; i-=2)
        {s += (cc_no[i]-'0') ;}
        //-------Final revel---------
    if (s%10==0)
            {std::cout<<"credit card number "<<cc_no<<" VALID!"; }
    else    {std::cout<<"credit card number "<<cc_no<<" INVALID!";}
}