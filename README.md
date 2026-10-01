# LearningCpp

This repo is my independent C++ journey that I started after high school, before heading into university, to figure out whether systems-level programming is actually where my interest lies before committing to it as a degree path.

There's no instructor assigning these projects and no syllabus dictating the order. Everything here is self-directed: I pick something I don't understand yet, build something small that forces me to understand it, and write down what I learn along the way so I can come back to it later.

## Why document this at all

A lot of what I'm learning right now will be obvious to me in six months and completely forgotten in eighteen. This repo is as much a reference for future-me as it is a public record; the `Notes/` folder exists specifically so that when I inevitably forget how something like `std::string`'s iterator functions work, I don't have to relearn it from scratch.

## Repo Structure

```
LearningCpp/
├── Notes/        — reference notes on language features, STL classes, and their common functions
└── projects/     — small, complete programs, each exploring a specific skill or concept
```

### `Notes/`

Reference material I write for myself while learning something new it's not polished documentation, just working notes with example code I can scan quickly later.

Currently covers:
- **`Strings_n_functions.cpp`** — `std::string` member functions (size/capacity, element access, iterators, modification, searching, numeric conversions), written as a runnable cheat sheet rather than a passive text file.

This folder will grow as I go. The plan is to eventually split it into subfolders by topic as it fills out by STL containers, classes and objects, algorithms — since right now it's just the one file, but I'm actively learning more string-related STL algorithms and a handful of other standard library classes that tend to share a lot of common function patterns, so documenting those side by side should make the overlaps easier to spot.

### `projects/`

Small, complete programs — each one picked specifically to force me to learn something I didn't understand before starting it, not because the project itself was the goal.

| Project | What it explores |
|---|---|
| **Calculator** | Basic input validation, `switch` logic, handling arithmetic edge cases (division/modulo by zero, invalid roots). |
| **Credit_card_validator** | String-to-digit manipulation, the Luhn algorithm, looping over a string from both directions. |
| **Markdown_Note_Taking_CLI** | A full CLI note-taking app — manual dynamic memory management (`new`/`delete[]`), structs, enums, persistent file storage, case-insensitive search, and validated user input throughout. The most developed project here so far; it has [its own README](projects/Markdown_Note_Taking_CLI/README.md) and [MIT license](projects/Markdown_Note_Taking_CLI/LICENSE). |

## Where This Is Headed

This is a living repo, not a finished one. A rough sense of what's next:

- Keep expanding `Notes/` as I pick up more of the STL with more string algorithms, new classes, and the patterns that repeat across them.
- Split `Notes/` into topic-based subfolders once there's enough there to warrant it.
- Keep adding projects that target a specific gap in my understanding, not just projects for the sake of having more projects.

If you've stumbled onto this repo: it's a personal learning log first, a portfolio second. Expect rough edges, half-finished notes, and code that gets noticeably better the further into the repo's history you look that's kind of the point.
