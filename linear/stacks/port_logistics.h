#ifndef PORT_LOGISTICS_H
#define PORT_LOGISTICS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Structure representing a shipping container node in a Stack (LIFO).
 */
typedef struct container {
    char id[20];            /**< Unique container identifier alphanumeric code */
    char destination[50];   /**< Final destination port of the container */
    char origin[50];        /**< Dispatch origin port of the container */
    float weight;           /**< Cargo mass weight in kilograms */
    struct container* next; /**< Pointer to the next container stacked underneath */
} container;

// Function Prototypes
void clear_buffer(void);
container* track_container_by_id(container* start, const char* id);
container* create_container(const char* id, const char* destination, const char* origin, float weight);
void push(container** top, const char* id, const char* destination, const char* origin, float weight);
void pop(container** top);
void display_port_yard(container* top);
void clear_port_yard(container** top);
void exit_system(void);

#endif // PORT_LOGISTICS_H
