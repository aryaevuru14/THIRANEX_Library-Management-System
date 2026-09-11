# Library Management System (C++)
A console-based Library Management System built in C++ using Object-Oriented Programming (OOP) concepts and persistent file handling. Designed to manage book inventories, member accounts, transaction tracking, and searching.

## Key Features
* **Book & Member Management:** Add new books and register members with validation to prevent duplicate IDs.
* **Issue & Return Processing:** Real-time availability checks, member verification, and dynamic status updates.
* **Search Functionality:** Case-insensitive search by book title or author name.
* **File Persistence:** Automatically loads state on startup and saves data to `books.txt` and `members.txt` upon exit.
* **Interactive CLI Interface:** Structured menu navigation with formatted tabular console output using `<iomanip>`.

## Tech Stack
* **Language:** C++11 or higher
* **Compiler:** `g++` (GCC / MinGW)
* **Storage Format:** Text files (`.txt`) via C++ File I/O (`<fstream>`)

## Getting Started
### Prerequisites
* A C++ compiler installed (e.g., GCC/MinGW) and configured in your system environment path.
### Compilation
Open your terminal in the project directory and run:
g++ LibraryManagementSystem.cpp -o LibraryManagementSystem

### Execution
Run the compiled executable:
* **Windows (PowerShell/CMD):**
```powershell
.\LibraryManagementSystem.exe

* **Linux / macOS:**
./LibraryManagementSystem

## File Structure
├── LibraryManagementSystem.cpp   # Core C++ source code
├── books.txt                      # Generated persistent book database
└── members.txt                    # Generated persistent member database
