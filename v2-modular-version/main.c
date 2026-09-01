#include "stock.h"

int main() {
    int total_registrations = 0;
    int current_capacity = INITIAL_CAPACITY;
    int choice;
    
    PRODUCTS *list = (PRODUCTS *) malloc(current_capacity * sizeof(PRODUCTS));
    
    if (list == NULL) { 
        printf("Critical Error: Initial system memory allocation failed!\n"); 
        return 1; 
    }
    
    /* Pull persistent database entries into runtime memory structures */
    load_from_file(&total_registrations, &current_capacity, &list);
    
    do {
        printf("\033[H\033[2J");
        
        printf("\n==============================================\n");
        printf("         WAREHOUSE INVENTORY SYSTEM           \n");
        printf("==============================================\n");
        printf(" [1] Register New Product\n");
        printf(" [2] List All Products\n");
        printf(" [3] Search Product by Code\n");
        printf(" [4] Update Product Stock Quantity\n");
        printf(" [5] Update Product Unit Price\n");
        printf(" [6] Delete/Remove a Product\n");
        printf(" [7] Calculate Economic Value of One Product\n");
        printf(" [8] Calculate Total Warehouse Value\n");
        printf(" [9] Wipe/Clear All Stock Records\n");
        printf(" [0] Exit System\n");
        printf("==============================================\n");
        printf("Choose an choice: ");
         
        if(scanf("%d", &choice) != 1) {
            printf("Invalid input type! Please enter numbers only.\n");
            clear_buffer();
            choice = -1;
            printf("\nPress ENTER to continue...");
            getchar();      
            continue;
        }
        clear_buffer(); 
        printf("\n");
        
        switch(choice) {
            case 1:
                register_products(&total_registrations, &current_capacity, &list);
                break;
                
            case 2:
                list_products(total_registrations, list);
                break;
            
            case 3:
                search_by_code(total_registrations, list);
                break;
            
            case 4:
                update_product_stock(total_registrations, list);
                break;
            
            case 5:
                update_product_price(total_registrations, list);
                break;
            
            case 6:
                delete_product(&total_registrations, list);
                break;
            
            case 7:
                calculete_only_product_stock(total_registrations, list);
                break;
            
            case 8:
                calculete_full_stock(total_registrations, list);
                break;
             
            case 9:
                clear_stock(&total_registrations, &current_capacity, &list);
                break;
            
            case 0:
                exit_system(list);
                break;
            
            default:
                printf("Invalid choice option! Try again.\n"); 
                break;   
        }
         
        if (choice != 0 && choice != -1) {
            printf("\nPress ENTER to return to menu...");
            getchar();
        }
        
    } while(choice != 0);
     
    return 0;
}
