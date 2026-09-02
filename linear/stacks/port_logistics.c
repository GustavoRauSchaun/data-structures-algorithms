#include "port_logistics.h"

/**
 * @brief Clears the standard input buffer to avoid issues with menu transitions.
 */
void clear_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Traverses the stack to find a container with a specific ID.
 * @param start Pointer to the top container of the yard stack.
 * @param id The target alphanumeric identifier string.
 * @return Pointer to the found container node, or NULL if not located.
 */
container* track_container_by_id(container* start, const char* id) {
    container* current = start;
    
    // Linear search traversal across the stack
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            return current; // Match found
        }
        current = current->next;
    }
    return NULL; // Container not found in the yard
}

/**
 * @brief Dynamically allocates memory and builds a new container node.
 * @return Pointer to the allocated container node.
 */
container* create_container(const char* id, const char* destination, const char* origin, float weight) {
    container* new_node = (container*)malloc(sizeof(container));
    
    // Memory allocation validation check
    if (new_node == NULL) {
        printf("ERROR! Failed to allocate memory!!!\n");
        exit(EXIT_FAILURE);
    }
    
    // Safe string boundary copies ensuring absolute null termination
    strncpy(new_node->id, id, sizeof(new_node->id) - 1);
    new_node->id[sizeof(new_node->id) - 1] = '\0';
    
    strncpy(new_node->destination, destination, sizeof(new_node->destination) - 1);
    new_node->destination[sizeof(new_node->destination) - 1] = '\0';
    
    strncpy(new_node->origin, origin, sizeof(new_node->origin) - 1);
    new_node->origin[sizeof(new_node->origin) - 1] = '\0';
    
    new_node->weight = weight;
    new_node->next = NULL;
    
    return new_node;
}

/**
 * @brief Pushes a new container onto the top of the port storage stack.
 * @details Validates unique IDs to prevent matching duplicates in the system.
 */
void push(container** top, const char* id, const char* destination, const char* origin, float weight) {
    // Structural guard clause against duplicates
    if (track_container_by_id(*top, id) != NULL) {
        printf("Container with ID: %s is already registered in the system....\n", id);
        return;
    }
    
    container* new_node = create_container(id, destination, origin, weight);
    
    // Link adjustment placing the new node on top of the stack
    new_node->next = *top;
    *top = new_node;
    
    printf("Container successfully stored in the port yard...\n");
}

/**
 * @brief Pops (unloads) the topmost container from the storage yard stack.
 */
void pop(container** top) {
    // Validation check for empty stack
    if (*top == NULL) {
        printf("No containers currently stored in the port yard....\n");
        return;
    }
    
    container* temp = *top;
    
    // Visual display log of metadata attributes before releasing memory
    printf("Container currently in loading process.....\n");
    printf("ID: %s.\n", temp->id);
    printf("DESTINATION: %s.\n", temp->destination);
    printf("ORIGIN: %s.\n", temp->origin);
    printf("WEIGHT: %.2fkg.\n", temp->weight);
    
    // Advance the head pointer down to the subsequent node
    *top = (*top)->next;
    
    // Reclaim dynamically allocated heap block to prevent leaks
    free(temp);
    
    printf("Loading process completed successfully!\n");
    printf("|------------------------------------------------------|\n");
}

/**
 * @brief Loops through the stack structure and logs all active items inside the yard.
 */
void display_port_yard(container* top) {
    if (top == NULL) {
        printf("The port storage yard is empty....\n");
        return;
    }
    
    container* current = top;
    printf("|--- CONTAINER PORT STORAGE YARD LOG ---|\n");
    
    int position = 1;
    // Iterate down the linked structural stack
    while (current != NULL) {
        printf("|--= Container Position (%d) =--|\n", position);
        printf("ID: %s.\n", current->id);
        printf("DESTINATION: %s.\n", current->destination);
        printf("ORIGIN: %s.\n", current->origin);
        printf("WEIGHT: %.2f kg.\n", current->weight);
        
        position++;
        current = current->next;
    }
    printf("|----------------------------------|\n");
}

/**
 * @brief Clears the entire port stack, freeing up all remaining containers.
 */
void clear_port_yard(container** top) {
    if (*top == NULL) {
        return;
    }
    
    // Iteratively wipe nodes until top points to NULL
    while (*top != NULL) {
        container* temp = *top;
        *top = (*top)->next;
        free(temp);
    }
    
    *top = NULL; // Explicit restructural safety assignment
}

/**
 * @brief Halts the interface and safely finishes application runtime lifecycle execution.
 */
void exit_system(void) {
    printf("Press ENTER to exit the menu....\n");
    clear_buffer();
    getchar(); // Catch intentional termination stroke
    exit(EXIT_SUCCESS);
}
