# MarkCLI

Building a note-taking and search tool entirely from scratch in C++ to level up my programming skills beyond basic syntax. 

## Why I'm Making This
Most tutorials just have you print "Hello World" or build tiny scripts. I wanted to build an actual command-line tool (CLI) that solves a real problem (taking quick notes without leaving the terminal) while forcing myself to learn how memory and data structures actually work in C++—without relying on pre-built high-level containers like `std::vector`.

## What I'm Learning / Tech Stack
* **Language:** Modern C++26
* **Core Concepts:** Manual heap allocation with pointers (`new` and `delete[]`), dynamic array resizing, string manipulation, and input flow control.

## Development Roadmap
I'm building this iteratively commit by commit:
1. **v1.0:** Project setup & roadmap *(Current)*
2. **Phase 1:** Setting up the interactive menu loop (`do-while` & `switch-case`)
3. **Phase 2:** Writing the dynamic memory and pointer logic for storage
4. **Phase 3:** Building the custom substring search engine
5. **Phase 4:** Adding file saving (`<fstream>`) so notes don't disappear when closed

## How to Run (Once Code is Added)
```bash
g++ -std=c++26 main.cpp -o markcli
./markcli