# Port Logistics Management System

A robust Terminal Interface (CLI) application developed in C to simulate a maritime port storage yard control tracking system. The core data structure relies on a dynamic, custom-allocated sequential **Stack (LIFO - Last In, First Out)** to efficiently manage, track, and dispatch heavy container units.

## 🚀 About the Developer & Journey

* **Learning Timeline:** This level of code architecture, modularization, and advanced memory handling was achieved after just **2.5 months of self-driven programming study**.
* **Development Time:** The complete system architecture—including requirements planning, structure design, data separation, modularity splitting, and defensive input parsing—was engineered from scratch and deployed in **just 5 hours** of continuous development.

---

## 📐 Project Architecture & Modularity

The software follows a professional modular architecture pattern, separating structure definitions, operational core business logic, and UI interface tracking routing layers into independent compilation units:

*   **`main.c`**: Manages the core command loop, processes interactive menu responses, and handles edge-case alphanumeric token crashes.
*   **`port_logistics.h`**: The module header interface declaring macro boundaries, the data structures, and function prototype bindings.
*   **`port_logistics.c`**: Implements the technical data structure manipulation, dynamic memory lifecycles, and input buffer flushes.

---

## 💾 Data Structures & LIFO Logic

The model maps stack-based yard container storage physically placed on top of each other. Due to crane operational limits, the last container arriving at the stack top position must be the first container dispatched.

### Structural Node Definition
```c
typedef struct container {
    char id[20];            /* Unique alphanumeric container string code */
    char destination[50];   /* Target dispatch destination port */
    char origin[50];        /* Source dispatch origin port */
    float weight;           /* Cargo mass weight metrics in kilograms */
    struct container* next; /* Reference linking pointer to the node underneath */
} container;
```

### Core Operations Included
1. **`Push`**: Places a validated container node onto the top position. Built-in linear searches ensure that duplicate ID tracking collisions are rejected before allocation.
2. **`Pop`**: Pops off the top element, logging active structural metadata traces right before invoking safe `free()` heap disposal handlers.
3. **`Track By ID`**: Triggers a fast downstream link traversal search to monitor elements stored in the stack layout without modifying structure alignment pointers.

---

## 🛠️ Compilation and Execution

This project has no external library dependencies and compiles on any machine equipped with a standard C compiler (GCC, Clang, or MSVC).

### Manual Terminal Compilation
Navigate into the root repository workspace directory and run:

```bash
gcc main.c port_logistics.c -o port_system
```

### Run the Application
* **Linux / macOS:**
  ```bash
  ./port_system
  ```
* **Windows Terminal / PowerShell:**
  ```cmd
  port_system.exe
  ```

---

## 🎮 Interactive Menu Reference

Upon launch, operators log transactions using standard numerical indices:

```text

 |---- PORT MANAGEMENT LOGISTICS SYSTEM ----|
 1 -=- Register New Container.
 2 -=- Dispatch/Transport Container (Pop).
 3 -=- View Port Storage Yard Log.
 4 -=- Track Container by ID.
 5 -=- Empty Entire Port Yard.
 0 -=- Exit Menu.
 Employee Choice Response: 
```

### Memory Management & Safety Bounds
* **Leak Protections**: Choosing option `5` or `0` triggers deep pipeline pointer wipes, recycling active memory nodes safely back to the OS pool.
* **Input Corruption Protection**: String limits use safety scans (`%19[^\n]`, `%49[^\n]`) avoiding catastrophic buffer overflow overwrites. Sub-menu controls also flush invalid alphabetical noise tokens automatically to maintain stability.
