#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "scientific_calculator.h"

/**
 * @brief Clears the standard input buffer.
 * @details Discards any remaining leftover characters (like newlines) from stdin 
 *          to prevent unexpected behavior during subsequent user inputs.
 */
void clear_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Checks whether the calculator history stack is empty.
 * @param top Pointer to the head (top) node of the history stack.
 * @return true if the stack contains no operations, false otherwise.
 */
bool is_history_empty(operation* top) {
    return (top == NULL);
}

/**
 * @brief Dynamically allocates and initializes a new operation history node.
 * @param description Text string detailing the mathematical operation performed.
 * @return Pointer to the newly allocated operation node on the heap.
 */
operation* create_operation(const char* description) {
    // Dynamic memory allocation for the structural node block
    operation* new_node = (operation*)malloc(sizeof(operation));
    
    // Safety guard clause checking for heap allocation failure
    if (new_node == NULL) {
        printf("ERROR!! Failed to allocate memory!\n");
        exit(EXIT_FAILURE);
    }
    
    // Safely copy operation string text up to boundary limits ensuring explicit null-termination
    strncpy(new_node->description, description, sizeof(new_node->description) - 1);
    new_node->description[sizeof(new_node->description) - 1] = '\0';
    
    // Initialize trailing structural linked pointer sequence to NULL
    new_node->next = NULL;
    return new_node;
}

/**
 * @brief Persists the current in-memory history stack sequence into a local text file.
 * @param top Pointer to the topmost tracking operation element node.
 */
void save_history_to_file(operation* top) {
    // Open the persistence target stream file in rewrite overwrite mode
    FILE* file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("WARNING: Could not open file to save history.\n");
        return;
    }

    // Traverse downstream linearly logging text lines sequentially
    operation* current = top;
    while (current != NULL) {
        fprintf(file, "%s\n", current->description);
        current = current->next;
    }
    fclose(file); // Flush and close file safely
}

/**
 * @brief Re-hydrates and loads historical logs back from the persistent text data store.
 * @param top Double pointer updating the root reference location pointer address.
 */
void load_history_from_file(operation** top) {
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        return; // File does not exist yet; normal behavior for fresh initial execution
    }

    char buffer[100];
    operation* temp_head = NULL;

    // Read the text file line by line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Strip out lingering trailing newline carriage return artifacts
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) > 0) {
            // Build standalone dynamic metadata container nodes
            operation* new_node = create_operation(buffer);
            new_node->next = temp_head;
            temp_head = new_node;
        }
    }
    fclose(file);

    // Reverse structural stacking order mechanics to maintain correct LIFO temporal hierarchy
    operation* current = temp_head;
    while (current != NULL) {
        operation* next_node = current->next;
        current->next = *top;
        *top = current;
        current = next_node;
    }
}

/**
 * @brief Pushes a newly executed calculation string log node onto the top of the history stack.
 * @param top Double pointer referencing the head pointer to allow persistent updates.
 * @param description The calculation record message to be added.
 */
void push(operation** top, const char* description) {
    // Construct the node
    operation* new_node = create_operation(description);
    
    // Adjust bindings pointing to old top, migrating new record as current head
    new_node->next = *top;
    *top = new_node;
    
    printf("Operation stored in history....\n");
    printf("|-----------------------------------------|\n");
    save_history_to_file(*top); // Instantly update background disk file mapping snapshot
}

/**
 * @brief Pops (removes/undos) the absolute latest operation recorded from the history stack.
 * @param top Double pointer updating reference address block of root tracking marker.
 */
void pop(operation** top) {
    // Bounds guard check preventing execution faults on unassigned lists
    if (top == NULL || is_history_empty(*top)) {
        printf("History is empty....\n");
        return;
    }
    
    // Cache targeting structural block layer before updating chain references
    operation* temp = *top;
    printf("Removing last operation: %s\n", temp->description);
        
    // Shift top assignment reference pointer level down to subsequent node item
    *top = (*top)->next;
    
    // Reclaim dynamically allocated memory blocks to prevent leaks
    free(temp);
    
    printf("Operation removed successfully....\n");
    printf("|-----------------------------------------------|\n");
    save_history_to_file(*top); // Re-sync modified internal list onto flat text file storage
}

/**
 * @brief Iterates downstream across active heap nodes logging full user log tracks.
 * @param top Pointer representing baseline reading coordinates.
 */
void display_history(operation* top) {
    if (top == NULL || is_history_empty(top)) {
        printf("History is empty....\n");
        return;
    }
    operation* current = top;
    printf("|--= LOG // SCIENTIFIC CALCULATOR HISTORY =--|\n");
    
    // Traverse down the structural linked nodes until tail sequence is hit
    while (current != NULL) {
         printf(" [Undo] -> %s\n", current->description);
         current = current->next;
    }
    printf("|------------------------------------------------|\n");
}

/**
 * @brief Purges and completely cleans up the entire memory log workspace.
 * @param top Double pointer to safely reset base node configuration target.
 */
void clear_history(operation** top) {
    if (top == NULL || is_history_empty(*top)) {
        printf("History is already empty.....\n");
        return;
    }
    
    // Sequentially detach active elements freeing tracking records down to the root base
    while (*top != NULL) {
        operation* temp = *top;
        *top = (*top)->next;
        free(temp);
    }
    *top = NULL; // Explicit safe re-structural assignment resetting
    
    printf("History completely deleted successfully!\n"); 
    printf("|----------------------------------------------|\n");
    save_history_to_file(*top); // Overwrite disk data clearing residual text records
}

/**
 * @brief Interactive processing submenu interface coordinating floating point calculation steps.
 * @param history Double pointer directly forwarding history updates downstream back onto core stacks.
 */
void calculate_operations(operation** history) {
    char aux[100]; // Buffer for compiling formatting trace string statements
    int op;
    float num1, num2, result;
    
    do {     
         printf("\n===============================================\n");
         printf("              MATH OPERATIONS                  \n");
         printf("===============================================\n");
         printf(" 1 - Addition (+)\n");
         printf(" 2 - Subtraction (-)\n");
         printf(" 3 - Multiplication (*)\n");
         printf(" 4 - Division (/)\n");
         printf(" 5 - Exponentiation (^)\n");
         printf(" 6 - Back.\n");
         printf("==============================================\n");
         printf(" User choice: ");
        
        // Input scanning filtering character stream traps protecting against fatal terminal loops
        if (scanf("%d", &op) != 1) {
            printf("Invalid option! Type only the option number.....\n");
            while (getchar() != '\n'); // Flush buffer stream completely
            op = -1;
            printf("\nPress ENTER to continue...");
            getchar();  
            continue;
        }
        while (getchar() != '\n'); // Pull lingering end tokens off scanner registers
        printf("\n");
        
        printf("\033[H\033[J"); // Clears the terminal screen layout area
        
        if (op < 1 || op > 6) {
            printf("Invalid operation! Try again.\n");
            continue;
        }
        if (op == 6) {
            printf("\033[H\033[J");
            return; // Gracefully pop workflow routing back to home runtime menu
        }
        
        printf("Enter the first value for the operation: ");
        if (scanf("%f", &num1) != 1) {
            printf("Invalid input! Try again...\n");
            clear_buffer();
            continue;
        }
        printf("Enter the second value for the operation: ");
        if (scanf("%f", &num2) != 1) {
            printf("Invalid input! Try again....\n");
            clear_buffer();
            continue;
        }
        
        // Match chosen branch processing routing assignments
        switch (op) {
            case 1:
                result = num1 + num2;
                sprintf(aux, "Addition: %.2f + %.2f = %.2f", num1, num2, result);
                break;
            case 2:
                result = num1 - num2;
                sprintf(aux, "Subtraction: %.2f - %.2f = %.2f", num1, num2, result);
                break;
            case 3:
                result = num1 * num2;
                sprintf(aux, "Multiplication: %.2f * %.2f = %.2f", num1, num2, result);
                break;
            case 4:
                // Runtime safety block catching and blocking invalid illegal mathematical expressions
                if (num2 == 0) {
                printf("ERROR!! Division by zero is not allowed!\n");
                continue;
                }
                result = num1 / num2;
                sprintf(aux, "Division: %.2f / %.2f = %.2f", num1, num2, result);
                break;

           case 5:
                result = powf(num1, num2); // Math library calculation mechanism step
                sprintf(aux, "Power: %.2f raised to %.2f = %.2f", num1, num2, result);
                break;
                } 

                printf(" RESULT: %.2f\n", result);
                push(history, aux); // Log evaluation text strings onto background history tracking pipelines
                } while (op != 6);
                }
                /**@brief Interface halt method performing explicit teardown cleanup procedures before exiting.*/
                void exit_system(void){
                printf("Press ENTER to exit the menu....\n");
                clear_buffer();
                exit(EXIT_SUCCESS); // Close runtime execution paths cleanly   
                }
