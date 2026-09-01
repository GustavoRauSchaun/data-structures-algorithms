# 📦 Inventory Control System

This is a complete inventory management system developed in C. The project was entirely designed and coded by me with **only 1.5 months of studies in the field**, taking about 5 hours of structured development.

The main goal was to apply fundamental concepts of structured programming, static memory allocation, and safe data manipulation to solve a real product logistics problem.

---

## 🚀 System Features

The program operates via an interactive terminal and offers a menu with 8 essential operations:
1. **Register Product:** Registration with automatic validation to prevent duplicate codes.
2. **List Products:** Organized display of all active items, avoiding reading junk data from memory.
3. **Search by Code:** Quick localization of a specific product in the database.
4. **Update Stock:** Exclusive modification of an item's available stock quantity.
5. **Update Price:** Dynamic adjustment of the financial value assigned to the product.
6. **Remove Product:** Logical deletion using a left-shift algorithm, maintaining the integrity and contiguity of the array.
7. **Calculate Total Stock Value:** Automated multiplication of the available volume by the unit price of a chosen item.
8. **Exit System:** Clean and safe console termination.

---

## 🧠 Technical Concepts Applied

To build this architecture in C, I demonstrated practical mastery in the following topics:
* **Data Structures (`typedef struct`):** Creation of the custom `PRODUCTS` type to encapsulate multiple properties (name, code, price, stock).
* **Pass By Reference (Pointers):** Use of references (`int *total_registrations`) to alter global counters directly from within the registration and removal functions.
* **Safe String Manipulation:** Implementation of format specifier masks (`%14[^\n]` and `%29[^\n]`) in `scanf` to prevent buffer overflow and allow spaces in names.
* **Scanning and Shift Algorithms:** Linear scanning for ID searches and physical movement of elements in the array to fill gaps after deletions.

---

## 🛠️ How to Run the Project

Make sure you have a GCC compiler configured on your system.

1. Clone this repository or download the source code file.
2. Open the terminal in the project folder and compile the code:
   ```bash
   gcc sistema_estoque.c -o inventory_system
   ```
3. Run the generated program:
   * **Windows:** `inventory_system.exe`
   * **Linux/Mac:** `./inventory_system`

---

## 📈 Future Improvements and Next Steps
As this is **Version 1.0 (MVP)**, the system uses static array memory allocation (limited to 300 records). As evolution goals for my upcoming months of study, I plan to implement:
* Dynamic Memory Allocation (`malloc`, `realloc`, and Linked Lists) to remove the fixed size limit.
* Data Persistence in Text or Binary Files (`fopen`, `fwrite`), allowing products to remain saved even after closing the program.
 to remove the fixed size limit.
