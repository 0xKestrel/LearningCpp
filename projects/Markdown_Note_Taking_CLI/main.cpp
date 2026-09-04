#include<iostream>
#include<string>

void ask_choice (int& a){

    std::cout<< "1. Create a Note\n"<<
                "2. List all Notes\n"<<
                "3. Search Notes\n"<<
                "4. Exit\n"<<
                "Select an Option: ";
    std::cin>> a;
}



int main(){

    std::cout<<"----- CLI Note Vault -----\n";
    int choice{};
    do
    {
        ask_choice(choice);
        
    } while (choice!=4);
    
}