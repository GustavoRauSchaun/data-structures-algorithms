#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definition of the node structure for the singly linked list
typedef struct node {
    int id;                      // Unique identifier for the task
    char description[100];       // String to store the task description
    struct node* next;           // Pointer to the next node in the list
} node;

// Function to allocate and initialize a new task node
node* create_task(const char* description, int id) {
    // Dynamic memory allocation for the new node
    node* new_node = (node*)malloc(sizeof(node));
    
    // Check if the memory allocation failed
    if (new_node == NULL) {
        printf("MEMORY ALLOCATION ERROR!!!\n");
        exit(1);
    }
    
    // Assigning the ID
    new_node->id = id;
    
    // Safe copying of the description string, ensuring null-termination
    strncpy(new_node->description, description, sizeof(new_node->description) - 1);
    new_node->description[sizeof(new_node->description) - 1] = '\0';
    
    // Initializing the next pointer to NULL
    new_node->next = NULL;
    return new_node;
}

// Function to insert a task at the end of the linked list
void insert_task(node** start, int id, const char* description) {
    // Creating the new task node using the helper function
    node* new_node = create_task(description, id);
    
    // If the list is empty, the new node becomes the start of the list
    if (*start == NULL) {
        *start = new_node;
    } 
    // Otherwise, traverse the list until the last node is reached
    else {
        node* current = *start;
        while (current->next != NULL) {
            current = current->next;
        }
        // Link the last node to the new node
        current->next = new_node;
    }
    printf("task %d added...\n", id);
}

// Function to remove a task from the list by its ID
void delete_task(node** start) {
    int search_id;
    
    // Check if the list is empty
    if (*start == NULL) {
        printf("no tasks registered....\n");
        return;
    }
    
    // Requesting the ID from the user
    printf("type the task ID: ");
    scanf("%d", &search_id);
    
    node* current = *start;
    node* previous = NULL;
    
    // Loop to find the node with the matching ID
    while (current != NULL && current->id != search_id) {
        previous = current;
        current = current->next;
    }
    
    // If the task was not found in the list
    if (current == NULL) {
        printf("task not found....\n");
        return;
    }
    
    // If the node to be removed is the first node
    if (previous == NULL) {
        *start = current->next;
    } 
    // If it is in the middle or at the end
    else {
        previous->next = current->next;
    }
    
    printf("task %d was completed...\n", search_id);
    free(current); // Freeing the allocated memory of the deleted node
}

// Function to print all pending tasks in the list
void display_tasks(node* start) {
    // Check if there are any tasks to show
    if (start == NULL) {
        printf("no tasks registered in the system...\n");
        return;
    }
    
    node* current = start;
    printf(" |---PENDING TASKS LIST---|\n");
    
    // Iterate through the list and print each task's details
    while (current != NULL) {
        printf(" ID: %d.\n DESCRIPTION: %s.\n", current->id, current->description);
        current = current->next;
    }
}

// Function to free all memory allocated by the system list
void clear_system(node** start) {
    node* current = *start;
    
    // Sequentially free each node
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }
    *start = NULL; // Reset the head pointer to NULL
}

// Helper function to print exit message
void exit_system() {
    printf("press ENTER to exit the menu....\n");
}

int main() {
    node* task_list = NULL; // Head of the linked list
    int id = 0;
    char description[100];
    int choice;
    
    do {
        // Main Menu Display
        printf(" |---TASKS MENU---|\n");
        printf(" 1 - insert task to the list.\n");
        printf(" 2 - remove a task from the list.\n");
        printf(" 3 - list pending tasks.\n");
        printf(" 4 - clear tasks list.\n");
        printf(" 0 - exit menu.\n");
        printf(" user response: ");
        
        // Input validation to ensure an integer is read
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Type a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        
        printf("\033[H\033[J"); // ANSI escape code to clear screen
        
        switch (choice) {
            case 1:
                printf("type the task ID NUM (integer): ");
                scanf("%d", &id);
                printf("type a short description of the task: ");
                scanf(" %99[^\n]", description);
                insert_task(&task_list, id, description);
                break;
                
            case 2:
                delete_task(&task_list);
                break;
                
            case 3:
                display_tasks(task_list);
                break;
                
            case 4:
                clear_system(&task_list);
                break;
                
            case 0:
                exit_system();
                break;
                
            default:
                printf("invalid option! try again....\n");
        }
    } while (choice != 0);
    
    return 0;
}
