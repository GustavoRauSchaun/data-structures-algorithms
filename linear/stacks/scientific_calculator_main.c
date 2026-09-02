#include <stdio.h>
#include "scientific_calculator.h"

int main(void) {
    operation* scientific_calculator_history = NULL;
    int choice;
    
    // Load persisted session data upon initiation
    load_history_from_file(&scientific_calculator_history);
    
    do {
        printf("\033[H\033[2J");
        
        printf("\n================================================\n");
        printf("           SCIENTIFIC CALCULATOR                \n");
        printf("================================================\n");
        printf(" 1 -=- Perform New Math Calculation.\n");
        printf(" 2 -=- Undo Last Operation.\n");
        printf(" 3 -=- View History.\n");
        printf(" 4 -=- Delete History.\n");
        printf(" 0 -=- Exit menu.\n");
        printf("================================================\n");
        printf(" User response: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid option! Type only the option number.....\n");
            while (getchar() != '\n');
            choice = -1;
            printf("\nPress ENTER to continue...");
            getchar();
            continue;
        }
        while (getchar() != '\n');
        printf("\n");
    
        switch (choice) {
            case 1:
                calculate_operations(&scientific_calculator_history);
                break;
            case 2:
                pop(&scientific_calculator_history);
                break;
            case 3:
                display_history(scientific_calculator_history);
                break;
            case 4:
                clear_history(&scientific_calculator_history);
                break;
            case 0:
                exit_system();
                break;
            default:
                printf("Invalid option! Try again....\n");
                break;  
        }
        
        if (choice != 0 && choice != 1) {
            printf("\nPress ENTER to continue...");
            getchar();
        }
        
    } while (choice != 0);
    
    clear_history(&scientific_calculator_history);
    return 0;
}
