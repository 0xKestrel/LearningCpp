#include <iostream>
#include <string>
#include <fstream>
#include <limits>

struct Note {
    std::string title;
    std::string content;
};

enum MenuChoice { CREATE = 1, LIST, SEARCH, DELETE, EXIT };

int get_valid_int(int min_val, int max_val) {
    int value{};
    while (true) {
        if (std::cin >> value && value >= min_val && value <= max_val) {
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number between "
                   << min_val << " and " << max_val << ": ";
    }
}

void ask_choice(int& choice) {
    std::cout << "1. Create a Note\n"
              << "2. List all Notes\n"
              << "3. Search Notes\n"
              << "4. Delete a Note\n"
              << "5. Exit\n"
              << "Select an Option: ";
    choice = get_valid_int(CREATE, EXIT);
}

void resize_notes(int& count, int& capacity, Note*& notes) {
    if (count >= capacity) {
        capacity *= 2;
        Note* new_notes = new Note[capacity];
        for (int i = 0; i < count; ++i) {
            new_notes[i] = notes[i];
        }
        delete[] notes;
        notes = new_notes;
    }
}

void load_notes(int& count, int& capacity, Note*& notes) {
    std::ifstream inFile("notes.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            resize_notes(count, capacity, notes);
            notes[count].title = line;
            if (std::getline(inFile, line)) {
                notes[count].content = line;
            }
            count++;
        }
        inFile.close();
        if (count > 0) {
            std::cout << "[Loaded " << count << " note(s) from notes.txt]\n\n";
        }
    }
}

void save_notes(int count, const Note* notes) {
    std::ofstream outFile("notes.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < count; ++i) {
            outFile << notes[i].title << "\n" << notes[i].content << "\n";
        }
        outFile.close();
    }
}

void print_title(const Note* notes, int i) {
    std::cout << i + 1 << ". " << notes[i].title << '\n';
}

void print_note(const Note* notes, int i) {
    std::cout << "--------------------------------------------------------------------\n"
               << "                             [Note: " << i + 1 << ".]\n"
               << "Title: " << notes[i].title << "\nContent: " << notes[i].content
               << "\n--------------------------------------------------------------------\n";
}

void input_n_output(int choice, int& count, int& capacity, Note*& notes) {
    switch (choice) {
        case CREATE: {
            resize_notes(count, capacity, notes);

            std::cin.ignore();
            std::cout << "\n----------------------------------------------------------------\n\nEnter note title: ";
            std::getline(std::cin, notes[count].title);
            std::cout << "Enter note content: ";
            std::getline(std::cin, notes[count].content);
            count++;
            std::cout << "Note saved successfully!\n\n----------------------------------------------------------------\n\n";
            save_notes(count, notes);
            break;
        }
        case LIST: {
            if (count == 0) {
                std::cout << "\nNo notes saved yet.\n\n";
                break;
            }
            std::cout << "Choose the type of List you want:\n1. Titles only\n2. Both the Title and the Content\n";
            int list_choice{ get_valid_int(1, 2) };

            std::cout << "\n---Your Notes---\n";
            if (list_choice == 1) {
                for (int i = 0; i < count; ++i) {
                    print_title(notes, i);
                }
            } else {
                for (int i = 0; i < count; ++i) {
                    print_note(notes, i);
                }
            }
            std::cout << '\n';
            break;
        }
        case SEARCH: {
            std::cin.ignore();
            std::string keyword;
            std::cout << "\nEnter keyword to search: ";
            std::getline(std::cin, keyword);

            bool found = false;
            std::cout << "\n--- Search Results ---\n";
            for (int i = 0; i < count; ++i) {
                if (notes[i].title.find(keyword) != std::string::npos ||
                    notes[i].content.find(keyword) != std::string::npos) {
                    std::cout << "[" << i + 1 << "] " << notes[i].title << "\n    " << notes[i].content << "\n\n";
                    found = true;
                }
            }
            if (!found) {
                std::cout << "No matching notes found for \"" << keyword << "\".\n\n";
            }
            break;
        }
        case DELETE: {
            std::cout << "\n[Delete a Note - coming soon]\n\n";
            break;
        }
        case EXIT: {
            std::cin.ignore();
            std::cout << "\nExiting MarkCLI. Goodbye!\n\n";
            break;
        }
    }
}

int main() {
    std::cout << "----- CLI Note Vault -----\n";
    int choice{};
    int capacity{5};
    int count{};
    Note* notes = new Note[capacity];

    load_notes(count, capacity, notes);

    do {
        ask_choice(choice);
        input_n_output(choice, count, capacity, notes);
    } while (choice != EXIT);

    std::cin.clear();
    std::cout << "\nPress Enter to exit...";
    std::cin.get();

    delete[] notes;
    return 0;
}