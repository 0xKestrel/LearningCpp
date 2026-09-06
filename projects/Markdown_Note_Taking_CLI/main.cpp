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

void input_n_output (int& a, int & b, int& d , std::string*& t, std::string*& c){
    switch (a){
        case 1:
            if (b>=d){
                d*=2;
                std::string* newT = new std::string[d];
                std::string* newC = new std::string[d];
                for (size_t i = 0; i < b; ++i){
                        newT[i]=t[i];
                        newC[i]=c[i];
                    }
                delete[] t;
                delete[] c;

                t = newT;
                c = newC;        
                        
            }
                        
            std::cin.ignore();
            std::cout<<"\n----------------------------------------------------------------\n\nEnter note title: ";
            std::getline(std::cin, t[b]);
            std::cout << "Enter note content: ";
            std::getline(std::cin, c[b]);
            b++;
            std::cout << "Note saved successfully!\n\n----------------------------------------------------------------\n\n";
            break;
        case 2:
            std::cout<<"\n ---Yours Notes ---\n";
            if (b == 0){
                std::cout << "No notes saved yet.\n";
            } else{
                for(int i {0}; i < b;++i){
                    std::cout << i + 1 << ". " << t[i] << '\n';
                }
            }
            std::cout << '\n';
            break;
        case 3:{
            std::cin.ignore();
            std::string keyword;
            std::cout << "\nEnter keyword to search: ";
            std::getline(std::cin, keyword);
    
            bool found = false;
            std::cout << "\n--- Search Results ---\n";
                for (size_t i = 0; i < b; ++i){
                    if (t[i].find(keyword) != std::string::npos || c[i].find(keyword) != std::string::npos){
                        std::cout << "[" << i + 1 << "] " << t[i] << "\n" << "    " << c[i] << "\n\n";
                        found = true;
                    }
                }
                if (!found){
                    std::cout << "No matching notes found for \"" << keyword << "\".\n\n";
                }
            break;
        }
        case 4:
            std::cin.ignore();
            std::cout << "\nExiting MarkCLI. Goodbye!\n\n";
            break;
        default:
            std::cout<<"---Invalid Input! Please select between 1 and 4.---\n\n";
            break;
        }
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
        input_n_output(choice, count, capacity, titles, contents);

    } while (choice!=4);
    delete[] titles;
    delete[] contents;
}