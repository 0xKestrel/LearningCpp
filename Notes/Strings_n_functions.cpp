#include<iostream>
#include<string>
#include <algorithm> // For std::reverse and std::sort

// Helper utility to format sections in the console output
void printHeader(const std::string& title) {
    std::cout << "\n========================================\n"
              << "  " << title << "\n"
              << "========================================\n";
}

// -----------------------------------------------------------------------------
// 1. SIZE & CAPACITY
// -----------------------------------------------------------------------------
void demoSizeAndCapacity() {
    printHeader("1. SIZE & CAPACITY");

    std::string str = "Hello, C++ World!";

    std::cout << "Original String : \"" << str << "\"\n"
              << "length()        : " << str.length() << " (Number of characters)\n"
              << "size()          : " << str.size()   << " (Identical to length())\n"
              << "capacity()      : " << str.capacity() << " (Allocated buffer size before reallocation)\n"
              << "empty()         : " << (str.empty() ? "true" : "false") << "\n";

    // Modifying size
    str.resize(5);
    std::cout << "\nAfter resize(5) : \"" << str << "\" (Truncates string)\n";

    str.clear();
    std::cout << "After clear()   : \"" << str << "\"\n"
              << "empty() now     : " << (str.empty() ? "true" : "false") << "\n"
              << "capacity() now  : " << str.capacity() << " (Capacity remains allocated)\n";
}

// -----------------------------------------------------------------------------
// 2. ELEMENT ACCESS
// -----------------------------------------------------------------------------
void demoElementAccess() {
    printHeader("2. ELEMENT ACCESS");

    std::string str = "CPP_String";

    std::cout << "String          : \"" << str << "\"\n"
              << "str[4]          : '" << str[4] << "' (Fast, no bounds check)\n"
              << "str.at(1)       : '" << str.at(1) << "' (Safe, throws std::out_of_range if invalid)\n"
              << "str.front()     : '" << str.front() << "' (First character)\n"
              << "str.back()      : '" << str.back() << "' (Last character)\n"
              << "str.c_str()     : " << str.c_str() << " (C-style null-terminated const char* pointer)\n";
}

// -----------------------------------------------------------------------------
// 3. ITERATORS & ALGORITHMS
// -----------------------------------------------------------------------------
void demoIterators() {
    printHeader("3. ITERATORS");

    std::string str = "GitHub";

    std::cout << "String          : \"" << str << "\"\n";

    // Dereferencing valid iterators
    std::cout << "*str.begin()    : '" << *str.begin() << "' (Points to first char)\n"
              << "*str.rbegin()   : '" << *str.rbegin() << "' (Points to last char)\n";

    /*
     * NOTE ON end() AND rend():
     * - str.end() points ONE PAST the last character ('\0'). Do NOT dereference (*str.end()).
     * - str.rend() points ONE BEFORE the first character. Do NOT dereference (*str.rend()).
     * - They are used solely as boundary markers for loops and algorithms.
     */

    std::cout << "\nLooping using Iterators: ";
    for (auto it = str.begin(); it != str.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Using iterators with <algorithm>
    std::reverse(str.begin(), str.end());
    std::cout << "After std::reverse : \"" << str << "\"\n";

    std::sort(str.begin(), str.end());
    std::cout << "After std::sort    : \"" << str << "\"\n";
}

// -----------------------------------------------------------------------------
// 4. MODIFYING & EDITING
// -----------------------------------------------------------------------------
void demoModifications() {
    printHeader("4. MODIFYING & EDITING");

    std::string str = "Base";
    std::cout << "Initial         : \"" << str << "\"\n";

    str += " Text";
    std::cout << "+= operator     : \"" << str << "\"\n";

    str.append("!");
    std::cout << "append(\"!\")     : \"" << str << "\"\n";

    str.push_back('?');
    std::cout << "push_back('?')  : \"" << str << "\"\n";

    str.pop_back();
    std::cout << "pop_back()      : \"" << str << "\"\n";

    // insert(index, string)
    str.insert(4, " Extended");
    std::cout << "insert(4, ...)  : \"" << str << "\"\n";

    // erase(startIndex, count)
    str.erase(4, 9);
    std::cout << "erase(4, 9)     : \"" << str << "\"\n";

    // replace(startIndex, count, newString)
    str.replace(0, 4, "Core");
    std::cout << "replace(0,4,..) : \"" << str << "\"\n";
}

// -----------------------------------------------------------------------------
// 5. SEARCHING & SUBSTRINGS
// -----------------------------------------------------------------------------
void demoSearchAndSubstrings() {
    printHeader("5. SEARCH & SUBSTRINGS");

    std::string str = "The quick brown fox jumps over the lazy dog";
    std::cout << "Text : \"" << str << "\"\n\n";

    // substr(startIndex, length)
    std::string sub = str.substr(4, 5); // Extracts "quick"
    std::cout << "str.substr(4, 5) : \"" << sub << "\"\n";

    // Searching
    size_t found = str.find("fox");
    if (found != std::string::npos) {
        std::cout << "find(\"fox\")      : Index " << found << "\n";
    }

    size_t lastFound = str.rfind("the");
    if (lastFound != std::string::npos) {
        std::cout << "rfind(\"the\")     : Index " << lastFound << " (Searches backwards)\n";
    }

    // Checking for non-existent substring
    size_t missing = str.find("cat");
    if (missing == std::string::npos) {
        std::cout << "find(\"cat\")      : Not Found (Returned std::string::npos)\n";
    }
}

// -----------------------------------------------------------------------------
// 6. NUMERIC CONVERSIONS
// -----------------------------------------------------------------------------
void demoConversions() {
    printHeader("6. CONVERSIONS (<string> utilities)");

    // Numbers to Strings
    int num {42};
    double pi {3.14159};
    std::string s1 {std::to_string(num)}, s2 {std::to_string(pi)};

    std::cout << "std::to_string(42)      : \"" << s1 << "\"\n"
              << "std::to_string(3.14159) : \"" << s2 << "\"\n";

    // Strings to Numbers
    std::string strInt {"100"}, strDouble  {"2.71828"} ;

    int parsedInt = std::stoi(strInt);
    double parsedDouble = std::stod(strDouble);

    std::cout << "std::stoi(\"100\")        : " << parsedInt << "\n"
              << "std::stod(\"2.71828\")    : " << parsedDouble << "\n";
}

// -----------------------------------------------------------------------------
// MAIN ENTRY POINT
// -----------------------------------------------------------------------------
int main() {
    std::cout << "===================================================\n"
              << "   C++ std::string MASTER CHEAT SHEET & REFERENCE  \n"
              << "===================================================\n";

    demoSizeAndCapacity();
    demoElementAccess();
    demoIterators();
    demoModifications();
    demoSearchAndSubstrings();
    demoConversions();

    std::cout << "\nExecution complete.\n";
    return 0;
}












































































/*
void in_str (std::string &input){
        std::cout<< "Enter yoir word...";
    std::getline(std::cin,input);
    std::cout<<"\nSo this is og input: "<<input;
}

void show_res(std::string &input){
        std::cout << 
        //------Size & Capacity------
        "\ninput.length: " <<input.length() <<
        "\ninput.size: " <<input.size() <<
        "\ninput.capacity: " <<input.capacity() <<
        "\ninput.empty: " << input.empty() <<
        //------Element Access------
        "\ninput[4]: " << input[4] <<
        "\ninput.at(3): " << input.at(3) <<
        "\ninput.front: " << input.front() << 
        "\ninput.back: " <<input.back() <<
        //------Iterators------
        "\ninput.begin: " << *input.begin() <<
        "\ninput.rbegin: " << *input.rbegin() << 
        "\ninput.end: " << *input.end() <<
        "\ninput.rend: " << *input.rend() <<
        "\ninput.find: " << input.find("a") <<
        "\ninput.rfind: " << input.rfind("a")<< 
        "\ninput.substr(4,6): " << input.substr(4,6) <<
        "\nSo this is og input: " << input ;
}
void clr_res(std::string &input){
         std::cout <<
        //------Size & Capacity------
        "\ninput.length: " <<input.length() <<
        "\ninput.size: " <<input.size() <<
        "\ninput.capacity: " <<input.capacity() <<
        "\ninput.empty: " << input.empty() <<
        //------Element Access------
        // cannot be run on a clear str
        //------Iterators------
        "\ninput.begin: " << *input.begin() <<
        "\ninput.rbegin: " << *input.rbegin() << 
        "\ninput.end: " << *input.end() <<
        "\ninput.rend: " << *input.rend() <<
        "\ninput.find: " << input.find("a") <<
        "\ninput.rfind: " << input.rfind("a") <<
        "\nSo this is og input: " << input ;
    
}

int main(){
    
                std::string u;
                    in_str(u);
                    show_res(u);

        //------Modifying & Editing Strings------
                    
        u.resize(5);    std::cout << "\n. \n. \n. \n u.resize(5) \n. \n. \n. \n";
                    show_res (u);
        u.clear();      std::cout << "\n. \n. \n. \n u.clear() \n. \n. \n. \n";
                    clr_res(u);

                std::string v;      std::cout << "\n. \n. \n. \n. \n. \n. \n. \n";
                    in_str(v);
                    show_res(v);
        v.append(" HaHaHa");         std::cout << "\n. \n. \n. \n v.append(HaHaHa) \n. \n. \n. \n";
                    show_res(v);
        v+=" Ohhh";                  std::cout << "\n. \n. \n. \n v+= Ohhh \n. \n. \n. \n";
                    show_res(v);
        v.push_back('!');            std::cout << "\n. \n. \n. \n v.push_back('!') \n. \n. \n. \n";
                    show_res(v);
        v.pop_back();                std::cout << "\n. \n. \n. \n v.pop_back() \n. \n. \n. \n";
                    show_res(v);
        v.insert(4," this is beeing added ");    std::cout << "\n. \n. \n. \n v.insert(4, '...') \n. \n. \n. \n";
                    show_res(v);
        v.erase(4,5);                std::cout << "\n. \n. \n. \n v.erase(4,5) \n. \n. \n. \n";
                    show_res(v);
        v.replace(5,2,"was");        std::cout << "\n. \n. \n. \n v.replace(5,2, '...') \n. \n. \n. \n";
                    show_res(v);


}*/