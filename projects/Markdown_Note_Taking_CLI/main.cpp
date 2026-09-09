#include<iostream>
#include<string>
#include <fstream>

void ask_choice (int& choice){

    std::cout<< "1. Create a Note\n"<<
                "2. List all Notes\n"<<
                "3. Search Notes\n"<<
                "4. Exit\n"<<
                "Select an Option: ";
    std::cin>> choice;
}

void resize_arrays(int& count, int& capacity, std::string*& titles, std::string*& contents) {
    if (count >= capacity) {
        capacity *= 2;
        std::string* newT = new std::string[capacity];
        std::string* newC = new std::string[capacity];
        for (size_t i = 0; i < count; ++i) {
            newT[i] = titles[i];
            newC[i] = contents[i];
        }
        delete[] titles;
        delete[] contents;
        titles = newT;
        contents = newC;
    }
}

void load_notes(int& count, int& capacity, std::string*& titles, std::string*& contents) {
    std::ifstream inFile("notes.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            resize_arrays(count, capacity, titles, contents); 
            titles[count] = line;
            if (std::getline(inFile, line)) {
                contents[count] = line;
            }
            count++;
        }
        inFile.close();
        if (count > 0) {
            std::cout << "[Loaded " << count << " note(s) from notes.txt]\n\n";
        }
    }
}

void save_notes(int& count, std::string*& titles, std::string*& contents){
    {    
         std::ofstream outFile("notes.txt");
            if (outFile.is_open()) {
                for (size_t i = 0; i < count; ++i) {
                    outFile << titles[i] << "\n" << contents[i] << "\n";
                }
                outFile.close();
            }
    }
    
   
}

void input_n_output(int& choice, int& count, int& capacity, std::string*& titles, std::string*& contents) {
    switch (choice) {
        case 1: {
            resize_arrays(count, capacity, titles, contents); 
                
            std::cin.ignore();
            std::cout << "\n----------------------------------------------------------------\n\nEnter note title: ";
            std::getline(std::cin, titles[count]);
            std::cout << "Enter note content: ";
            std::getline(std::cin, contents[count]);
            count++;
            std::cout << "Note saved successfully!\n\n----------------------------------------------------------------\n\n";
            save_notes(count, titles, contents);
            
            break;
        }
        case 2: {
            std::cout << "\n ---Your Notes---\n";
            if (count == 0) {
                std::cout << "No notes saved yet.\n";
            } else {
                for (size_t i{0}; i < count; ++i) {
                    std::cout << i + 1 << ". " << titles[i] << '\n';
                }
            }
            std::cout << '\n';
            break;
        }
        case 3: {
            std::cin.ignore();
            std::string keyword;
            std::cout << "\nEnter keyword to search: ";
            std::getline(std::cin, keyword);
    
            bool found = false;
            std::cout << "\n--- Search Results ---\n";
            for (size_t i = 0; i < count; ++i) {
                if (titles[i].find(keyword) != std::string::npos || contents[i].find(keyword) != std::string::npos) {
                    std::cout << "[" << i + 1 << "] " << titles[i] << "\n    " << contents[i] << "\n\n";
                    found = true;
                }
            }
            if (!found) {
                std::cout << "No matching notes found for \"" << keyword << "\".\n\n";
            }
            break;
        }
        case 4: {
            std::cin.ignore();
            std::cout << "\nExiting MarkCLI. Goodbye!\n\n";
            break;
        }
        default: {
            std::cout << "---Invalid Input! Please select between 1 and 4.---\n\n";
            break;
        }
    }
}

int main() {
    std::cout << "----- CLI Note Vault -----\n";
    int choice{};
    int capacity{5};
    int count{};
    std::string* titles = new std::string[capacity];
    std::string* contents = new std::string[capacity];

    load_notes(count, capacity, titles, contents);

    do {
        ask_choice(choice);
        input_n_output(choice, count, capacity, titles, contents);
    } while (choice != 4);

    std::cin.clear();
    std::cin.ignore(32767, '\n');

    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    
    delete[] titles;
    delete[] contents;
    return 0;
}