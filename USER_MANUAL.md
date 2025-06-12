# DCDL Helper — User Manual

DCDL Helper is a C++ command-line tool for solving Countdown-style Letters and Numbers rounds. 

---

## Requirements

- C++17 compatible compiler (e.g., g++ 7+ or clang 6+)
- [CMake](https://cmake.org/) 3.10 or newer
- [vcpkg](https://github.com/microsoft/vcpkg) (for dependency management)
- [Ninja](https://ninja-build.org/) build system (used as the linker by default)
- [exprtk](https://github.com/ArashPartow/exprtk) libraries (installed automatically via vcpkg)

---

## Environment Setup

Before building, you **must** set the `VCPKG_ROOT` environment variable to the path where vcpkg is installed. This is required because the build system uses `${VCPKG_ROOT}` in the CMake toolchain path (see `CMakePresets.json`).

Example (Linux/macOS):

```sh
export VCPKG_ROOT=/path/to/vcpkg
```

Replace `/path/to/vcpkg` with the actual path to your vcpkg installation directory.

To verify that `VCPKG_ROOT` is set correctly, run:

```sh
echo $VCPKG_ROOT
```

This should print the path to your vcpkg directory. 

---

## Using the Makefile

You can also build and run the project using the provided Makefile:

- To build the project:
  ```sh
  make build
  ```
- To build and run the program:
  ```sh
  make run
  ```
- To clean the build directory:
  ```sh
  make clean
  ```
- To just build (default target):
  ```sh
  make
  ```

---

## Main Menu

When you start the program, you will see:

```
Choose a round to play:
  1. Letters Round
  2. Numbers Round
  3. Exit
> 
```
Enter `1` for Letters Round, `2` for Numbers Round, or `3` to exit.

---

## Letters Round

You can now choose how to input your letters:

```
Choose input mode: (m)anual or (s)Vowel/Consonant selection mode?
```
- **Manual mode (`m` or `M`)**: Enter all letters yourself.
- **Vowel/Consonant selection mode (`s` or `S`)**: Select each letter as a vowel or consonant. The program will randomly pick a letter from the chosen group.

### Vowel/Consonant Selection Mode Example
```
Choose input mode: (m)anual or (s)Vowel/Consonant selection mode? s
Choose letter 1 (v for vowel, c for consonant, done to finish): v
Choose letter 2 (v for vowel, c for consonant, done to finish): c
... (repeat until done)
Generated letters: ABL...
```

### After Letter Selection
- The program finds all valid words from your letters using the dictionary.
- You will see the number of valid words and can explore them with commands:

#### Letters Round Commands
- `next N` — Show the next N words.
- `prev N` — Show the previous N words.
- `range A B` — Show words from position A to B.
- `back` — Return to the main menu.
- `exit` — Quit the program.

---

## Numbers Round

You can solve for a target number using arithmetic operations and a set of numbers. You can also add custom operations.

### Numbers Round Commands
- `solve` — Enter numbers and a target to solve.
- `addop` — Add a custom operation using ExprTk syntax (e.g., `x*x + y`).
- `listop` — List all available operations.
- `back` — Return to the main menu.
- `exit` — Quit the program.

#### Example: Solving a Numbers Round
1. Type `solve` and press Enter.
2. Enter up to 6 numbers separated by spaces.
3. Enter the target number.
4. The program will display the best solutions found.

#### Example: Adding a Custom Operation
1. Type `addop` and press Enter.
2. Enter a name for the operation (e.g., `cube`).
3. Enter an expression using `x` and `y` (e.g., `x*x*x + y`).
4. The operation is added and can be used in future solves.

---

## Dictionary File
- The dictionary file should be at `data/words.txt`.
- It must be a plain text file with one word per line.
