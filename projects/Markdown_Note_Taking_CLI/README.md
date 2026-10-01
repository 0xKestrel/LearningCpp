# MarkCLI — CLI Note Vault

Building a note-taking and search tool entirely from scratch in C++ to level up my programming skills beyond basic syntax.

```
----- CLI Note Vault -----
1. Create a Note
2. List all Notes
3. Search Notes
4. Delete a Note
5. Exit
Select an Option:
```

## Why I'm Making This

Most tutorials just have you print "Hello World" or build tiny scripts. I wanted to build an actual command-line tool that solves a real problem — taking quick notes without leaving the terminal — while forcing myself to learn how memory and data structures actually work in C++, without leaning on pre-built high-level containers like `std::vector`.

## What I'm Learning / Tech Stack

* **Language:** Modern C++ (C++23)
* **Core concepts:** manual heap allocation with pointers (`new` / `delete[]`), dynamic array resizing, structs, enums, string manipulation, and robust input validation.

## Features

- **Create** — add a note with a title and content.
- **List** — view just titles, or titles with full content, your choice.
- **Search** — find notes by keyword (case-insensitive) or jump straight to one by its number.
- **Delete** — remove a note by number, with a confirmation step that shows the full note before it's gone.
- **Persistence** — notes save to `notes.txt` after every change and reload automatically on startup.
- **Input-safe** — every menu and number prompt rejects non-numeric input and out-of-range values instead of crashing or looping forever.

## Getting Started

### Requirements

A compiler with **C++23** support — this project uses `std::string::contains`, which isn't available on older standards. In practice: GCC 13+, Clang 16+, or a recent MSVC. Compiling with an older standard (e.g. `-std=c++17`) will fail.

### Build

```bash
g++ -std=c++23 main.cpp -o markcli
```

This compiles `main.cpp` into a runnable program named `markcli` (`markcli.exe` on Windows).

### Run

```bash
./markcli
```

On startup, MarkCLI looks for a `notes.txt` file in the same folder and loads any notes it finds. If none exists yet, it just starts empty — the file gets created the first time you save a note.

## How Notes Are Stored

Each note is written as two lines in `notes.txt`: the title, then the content.

```
Grocery List
Milk, eggs, bread, coffee
Project Idea
A CLI note app with search and delete
```

Plain text, by design — readable, diffable, and easy to inspect or back up without any special tooling.

## Project Structure

Everything currently lives in a single `main.cpp`, organized into small, single-purpose functions:

| Function | Responsibility |
|---|---|
| `get_valid_int(min, max)` | Reads an integer from the user, re-prompting until it's both parseable and in range. Used everywhere a menu or note number is requested. |
| `ask_choice` | Displays the main menu and reads a validated choice. |
| `resize_notes` | Doubles the notes array's capacity when it fills up. |
| `load_notes` / `save_notes` | Read/write notes to `notes.txt`. |
| `print_title` / `print_note` | Print one note's title, or one note in full. |
| `to_lower` | Returns a lowercased copy of a string, used to make search case-insensitive without touching the original note data. |
| `input_n_output` | Routes the user's menu choice to the right feature. |

Notes are stored as a dynamically-resizing array of a `Note` struct:

```cpp
struct Note {
    std::string title;
    std::string content;
};
```

Growth works like a simplified `std::vector`: capacity starts at 5 and doubles whenever the note count catches up to it, with existing notes copied into the new array before the old one is freed.

## Design Notes

A few deliberate choices worth knowing if you're reading the code:

- **Validated input lives in one place.** `get_valid_int` is the only function that talks directly to `std::cin` for numeric input — it clears the stream's fail state and discards bad input on a failed read, then re-prompts. Every menu and "pick a note by number" step reuses it instead of re-implementing the same retry loop.
- **Searching never mutates your notes.** `to_lower` returns a new string rather than editing in place, so the lowercase comparison used for search has zero effect on how your notes are actually stored or displayed.
- **User-facing numbers are 1-based, array indices are 0-based.** The subtraction from one to the other happens right at the point a note number is turned into an array index, kept consistent across Search-by-number and Delete.

## Development Roadmap

Built iteratively, commit by commit:

- [x] **Phase 1** — Interactive menu loop (`do-while` & `switch-case`)
- [x] **Phase 2** — Dynamic memory and pointer logic for storage
- [x] **Phase 3** — File saving (`<fstream>`) so notes persist between runs
- [x] **Phase 4** — Search, including case-insensitive keyword matching
- [x] **Phase 5** — Delete, with confirmation before removal
- [x] Input validation on every numeric prompt
- [ ] Edit an existing note
- [ ] Reject empty titles on creation
- [ ] Export/save-as to a custom filename

## License

This project is licensed under the MIT License — see [LICENSE](LICENSE) for details.