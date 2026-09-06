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

void input_n_output (int& a ){
        
}

int main(){

    std::cout<<"----- CLI Note Vault -----\n";
    int choice{};
    int capacity{5};
    int count{};
    std::string* titles = new std::string [capacity];
    std::string* contents = new std::string[capacity];
    do
    {
        ask_choice(choice);
        switch (choice)
        {
        case 1:
            std::cin.ignore();
            std::cout<<"\n----------------------------------------------------------------\n\nEnter note title: ";
            std::getline(std::cin, titles[count]);
            std::cout << "Enter note content: ";
            std::getline(std::cin, contents[count]);
            count++;
            std::cout << "Note saved successfully!\n\n----------------------------------------------------------------\n\n";
            break;
        case 2:
            std::cout<<"\n ---Yours Notes ---\n";
            if (count == 0)
            {
                std::cout << "No notes saved yet.\n";
            } else{
                for(int i {0}; i < count;++i){
                    std::cout << i + 1 << ". " << titles[i] << '\n';
                }
            }
            std::cout << '\n';
            break;
        case 3:
            std::cin.ignore();
            std::cout<<"\n ---Feature Upcoming---\n\n";
            break;
        case 4:
            std::cin.ignore();
            std::cout << "\nExiting MarkCLI. Goodbye!\n\n";
            break;
        default:
            std::cout<<"---Invalid Input! Please select between 1 and 4.---\n\n";
            break;
        }

    } while (choice!=4);
    delete[] titles;
    delete[] contents;
}