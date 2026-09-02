# Scientific Calculator with Persistent History Stack

A professional Terminal Interface (CLI) scientific calculator application developed in C. This project implements a fully dynamic **Stack data structure (LIFO - Last In, First Out)** to handle a fully functioning "Undo" history system, alongside automated file-handling routines to store and load previous sessions.

> 💡 **Developer's Journey:** This project marks an advanced milestone achieved after **2.5 months of intensive software engineering studies**. The full system architecture, math routing modules, and pointer-based file persistence layers were successfully developed and modularized in a single **4-hour coding session**.

## 📐 Project Architecture & Modularity

The codebase is organized following strict clean-code modular design patterns, separating structure abstractions, input validation safeguards, and runtime UI configurations:

*   **`main.c`**: Initializes session states, reloads disk files upon initialization, and drives the central system shell menu loop.
*   **`scientific_calculator.h`**: The architectural contract containing data definitions, dynamic type nodes, and functional prototypes.
*   **`scientific_calculator.c`**: Implements pointer manipulations, stack logic, math parsing, and local file I/O pipelines.

---

## 💾 Stack Mechanics & Data Persistence

The calculation logging history operates using classic stack properties, where the absolute latest calculation is placed on top. Clicking "Undo" pops the top node off the pile and frees its space.

### Structural Node Definition
```c
typedef struct operation {
    char description[100];     /* Formatted mathematical trace text string */
    struct operation* next;    /* Reference linking pointer to the previous operation node */
} operation;
```

### Advanced Features Included
*   **Persistent Memory Stack**: Every time an operation is processed (`Push`), popped (`Pop`), or cleared, a background serialization worker instantly replicates the running memory stack data straight onto a local flat text file (`history.txt`).
*   **Automatic Session Re-Hydration**: Upon opening the software, a loading algorithm reads `history.txt` and rebuilds the stack structure in memory, perfectly preserving chronological LIFO order.
*   **Anti-Crash Terminal Shield**: Built-in scanner traps validate incoming user input streams. If an alphabetical character or invalid token is supplied, the program intercepts it, purges the input buffer, and prevents catastrophic infinite screen printing loops.

---

## 🛠️ Compilation and Execution

Compile the unified modules with any standard C compiler (like GCC):

### Manual Terminal Compilation
```bash
gcc main.c scientific_calculator.c -o scientific_calc -lm
```
*(Note: The `-lm` flag links the C math library required for power processing).*

### Run the Application
* **Linux / macOS:** `./scientific_calc`
* **Windows (CMD / PowerShell):** `scientific_calc.exe`

---

## 🎮 Interactive Menu Reference

Upon launch, users process transactions using standard numerical indices:

```text
================================================
           SCIENTIFIC CALCULATOR                
================================================
 1 -=- Perform New Math Calculation.
 2 -=- Undo Last Operation.
 3 -=- View History.
 4 -=- Delete History.
 0 -=- Exit menu.
================================================
 User response: 
```

### Supported Mathematical Operations
1. **Addition (`+`)**
2. **Subtraction (`-`)**
3. **Multiplication (`*`)**
4. **Division (`/`)** *(Includes standard zero-division safety protection checks)*
5. **Exponentiation (`^`)** *(Powered by standard floating-point `powf` implementations)*
