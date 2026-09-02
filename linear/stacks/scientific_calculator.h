#ifndef SCIENTIFIC_CALCULATOR_H
#define SCIENTIFIC_CALCULATOR_H

#include <stdbool.h>

#define FILENAME "history.txt"

/**
 * @brief Structure representing a single math operation node in the stack.
 */
typedef struct operation {
    char description[100];     /**< String containing the formatted operation text */
    struct operation* next;    /**< Pointer to the next operation in the stack */
} operation;

// --- Core Stack Functions ---
void clear_buffer(void);
bool is_history_empty(operation* top);
operation* create_operation(const char* description);
void push(operation** top, const char* description);
void pop(operation** top);
void display_history(operation* top);
void clear_history(operation** top);

// --- Math & Menu Functions ---
void calculate_operations(operation** history);
void exit_system(void);

// --- Data Persistence Functions ---
void save_history_to_file(operation* top);
void load_history_from_file(operation** top);

#endif // SCIENTIFIC_CALCULATOR_H
