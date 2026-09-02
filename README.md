# 📦 Warehouse stock System

Welcome to my stock Control portfolio project. This repository is designed to showcase my **programming evolution and learning curve in C**, demonstrating how a project can mature from basic structured logic into a professional, modular, and dynamic system.

The repository is explicitly split into two versions to highlight this technical growth.

---

💡 **Fun Fact & Context:** The **Version 1** of this dynamic list was coded during my **very first week of university**. Because I spent the previous two months self-studying low-level computer science concepts and C memory architecture, I managed to build functional node-linking structures.

---

## 📂 Repository Structure

* [**`v1-static-version/`**](./v1-static-version)
  * **Context:** Developed with only **1.5 months of study** (approx. 5 hours of development).
  * **Architecture:** Monolithic single-file program (`STOCK_CONTROL.c`) with static memory allocation (`array` capped at 300 records).
* [**`v2-modular-version/`**](./v2-modular-version)
  * **Context:** Developed with only **2.5 months of study** (approx. 4 hours of development).
  * **Architecture:** Fully modularized project using header (`.h`) and source (`.c`) files, data persistence, and professional error handling.

---

## 🚀 Version 2.0 Features & Technical Upgrades

The current main version (`v2-modular-version`) expands the system to 10 automated management features, using a secure, bulletproof terminal interface:
1. **Register New Product:** With pointer-driven array expansion and code uniqueness validation.
2. **List All Products:** Renders active runtime data while strictly ignoring unallocated memory slots.
3. **Search Product by Code:** High-speed item identification.
4. **Update Product Stock Quantity:** Targeted data manipulation.
5. **Update Product Unit Price:** Real-time evaluation adjustment.
6. **Delete/Remove a Product:** Memory-safe item removal with array contiguity maintenance.
7. **Calculate Individual Economic Value:** Stock quantity multiplied by its unit price.
8. **Calculate Total Warehouse Value:** Full inventory matrix reduction to deliver a total financial evaluation.
9. **Wipe/Clear All Records:** Complete memory reset.
10. **Data Persistence & Safe Exit:** Automated file serialization and dynamic memory freeing.

---

## 🧠 Advanced Computer Science Concepts Applied (V2.0)

* **Dynamic Memory Allocation:** Implemented manual heap management using `malloc` (and realloc/free in underlying headers) to remove all hardcoded database capacity limits.
* **Architecture Modularization (`.h` / `.c`):** Created clear abstraction layers by separating definitions (`stock.h`) from functional implementations, enforcing clean code principles.
* **File I/O Persistence:** Built-in automatic database serialization (`load_from_file`) ensuring your store data survives execution cycles by saving straight to the hard drive.
* **Input Stream & Buffer Validation:** Anti-crash interface engineering. The menu validates input types (`scanf("%d") != 1`) and isolates errors using a dedicated `clear_buffer()` mechanism to block infinite loop bugs.

---

## 🛠️ How to Compile and Run (V2.0)

Make sure you have a working GCC compiler environment.

1. Navigate to the advanced version directory:
   ```bash
   cd v2-modular-version
   ```
2. Compile all decoupled module files at once:
   ```bash
   gcc *.c -o warehouse_system
   ```
3. Run the compiled executable binary:
   * **Windows:** `warehouse_system.exe`
   * **Linux/Mac:** `./warehouse_system`
ed even after closing the program.
 to remove the fixed size limit.
