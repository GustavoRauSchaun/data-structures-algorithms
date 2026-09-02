#include "port_logistics.h"

int main(void) {
    container* yard_stack_top = NULL;
    float weight;
    char id[20], destination[50], origin[50];
    int choice;
    
    do {
        printf("\n |---- PORT MANAGEMENT LOGISTICS SYSTEM ----|\n");
        printf(" 1 -=- Register New Container.\n");
        printf(" 2 -=- Dispatch/Transport Container (Pop).\n");
        printf(" 3 -=- View Port Storage Yard Log.\n");
        printf(" 4 -=- Track Container by ID.\n");
        printf(" 5 -=- Empty Entire Port Yard.\n");
        printf(" 0 -=- Exit Menu.\n");
        printf(" Employee Choice Response: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid selection! Please enter numbers only.....\n");
            while (getchar() != '\n');
            choice = -1;
            continue;
        }
        while (getchar() != '\n');
        printf("\033[H\033[J");
        
        switch (choice) {
            case 1:
                printf("|--= REGISTER NEW CONTAINER =--|\n");
                printf("ID Code: ");
                scanf(" %19[^\n]", id);
                clear_buffer();
                
                printf("Destination Port: ");
                scanf(" %49[^\n]", destination);
                clear_buffer();
                
                printf("Origin Port: ");
                scanf(" %49[^\n]", origin);
                clear_buffer();
                
                printf("Weight (kg): ");
                scanf("%f", &weight);
                clear_buffer();
                printf("|-------------------------|\n");
                
                push(&yard_stack_top, id, destination, origin, weight);
                break;
                
            case 2:
                pop(&yard_stack_top);
                break;
                
            case 3:
                display_port_yard(yard_stack_top);
                break;
                
            case 4:
                printf("|---= TRACK CONTAINER =---|\n");
                printf("Enter target ID for scanning tracking: ");
                scanf(" %19[^\n]", id);
                clear_buffer();
                
                container* traced_node = track_container_by_id(yard_stack_top, id);
                
                if (traced_node != NULL) {
                    printf("|---= CONTAINER FOUND EN ROUTE! =---|\n");
                    printf("ID: %s.\n", traced_node->id);
                    printf("DESTINATION: %s.\n", traced_node->destination);
                    printf("ORIGIN: %s.\n", traced_node->origin);
                    printf("WEIGHT: %.2f kg.\n", traced_node->weight);
                    printf("|--------------------------------|\n");
                } else {
                    printf("Container with ID: %s is not stored at this port terminal yard.\n", id);
                }
                break;
                
            case 5:
                clear_port_yard(&yard_stack_top);
                printf("Transport operation finished! Yard cleared.\n");
                break;
                
            case 0:
                clear_port_yard(&yard_stack_top);
                exit_system();
                break;
                
            default:
                printf("Invalid selection option! Please try option range again.\n");
                break;      
        }
    } while (choice != 0);
    
    clear_port_yard(&yard_stack_top);
    return 0;
}
