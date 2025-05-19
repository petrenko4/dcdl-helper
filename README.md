# DCDL Helper

A C++ command-line tool for solving Countdown-style Letters and Numbers rounds.

## Features
- Letters Round: Find and explore all valid words from a set of letters using a dictionary.
- Numbers Round: Solve for a target number using arithmetic operations and a set of numbers. Supports custom operations via ExprTk expressions.

## Requirements
- C++17 compatible compiler (e.g., g++ 7+ or clang 6+)
- [CMake](https://cmake.org/) 3.10 or newer
- [vcpkg](https://github.com/microsoft/vcpkg) (for dependency management)
- [fmt](https://github.com/fmtlib/fmt) and [exprtk](https://github.com/ArashPartow/exprtk) libraries (installed automatically via vcpkg)

## Building

1. **Install dependencies with vcpkg:**
   ```sh
   ./vcpkg install
   ```
   (Or use your system's vcpkg if already set up.)

2. **Configure and build with CMake:**
   ```sh
   cmake -B build -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake
   cmake --build build
   ```
   Replace `<path-to-vcpkg>` with the path to your vcpkg installation. For example, if you installed vcpkg in your home directory, use `~/vcpkg/scripts/buildsystems/vcpkg.cmake`.
   The executable will be placed in `build/bin/dcdl-helper`.

## Running

From the project root, run:
```sh
./build/bin/dcdl-helper
```

- The program will prompt you to choose between Letters Round and Numbers Round.
- For Letters Round, you will need a dictionary file at `data/words.txt` (included in the repo or provide your own).

## Usage

- **Letters Round:**
  - Enter the letters when prompted.
  - Use commands like `next N`, `prev N`, `range A B`, `back`, or `exit` to explore results.

- **Numbers Round:**
  - Use commands:
    - `solve` — Enter numbers and a target to solve.
    - `addop` — Add a custom operation using ExprTk syntax.
    - `listop` — List available operations.
    - `back` or `exit` — Return to menu or quit.

## Notes
- The dictionary file should be a plain text file with one word per line.
- You can add or modify operations in Numbers Round as needed.