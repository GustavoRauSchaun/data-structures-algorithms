#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

// Maximum capacity of the static array
#define MAX_REGISTRATIONS 300 

typedef struct { 
    char name[30]; 
    char code[15]; 
    float price; 
    int stock; 
} PRODUCTS; 

// Helper function to scan the array and prevent duplicate product codes
int find_index_by_code(char *code, int total_registrations, PRODUCTS list[]) { 
    for(int i = 0; i < total_registrations; i++) { 
        if(strcmp(list[i].code, code) == 0) { 
            return i; // Returns the index if the product exists
        } 
    } 
    return -1; // Returns -1 if the product is not found
} 

void register_products(int *total_registrations, PRODUCTS list[]) { 
    // Boundary check to prevent array overflow
    if((*total_registrations) < MAX_REGISTRATIONS) { 
        char temporary_code[15]; 
        printf("|--PRODUCT TO BE REGISTERED--|=(%d)\n", (*total_registrations) + 1); 
        printf("CODE: "); 
        scanf(" %14[^\n]", temporary_code); 

        // Validation: Ensures uniqueness of the product identifier
        if(find_index_by_code(temporary_code, *total_registrations, list) != -1) { 
            printf("\n Code rejected! Code already registered in the system!\n"); 
            return; 
        } 

        // Storing data into the current active slot of the array
        strcpy(list[*total_registrations].code, temporary_code); 
        printf("NAME: "); 
        scanf(" %29[^\n]", list[*total_registrations].name); 
        printf("PRICE: "); 
        scanf("%f", &list[*total_registrations].price); 
        printf("IN STOCK: "); 
        scanf("%d", &list[*total_registrations].stock); 
        
        // Incrementing the global counter through its pointer reference
        (*total_registrations)++; 
        printf("\nRegistration completed successfully!\n"); 
    } else { 
        printf("Registration system full!\n"); 
    } 
} 

void list_products(int total_registrations, PRODUCTS list[]) { 
    if(total_registrations == 0) { 
        printf("No products registered in the system!\n"); 
    } else { 
        printf("|--REGISTERED PRODUCTS--|\n"); 
        // Iterates only through valid registered entries, avoiding junk memory data
        for(int i = 0; i < total_registrations; i++) { 
            printf("NAME: %s.\n", list[i].name); 
            printf("CODE: %s.\n", list[i].code); 
            printf("PRICE: %.2f-USD$.\n", list[i].price); 
            printf("IN STOCK: %d-packages.\n", list[i].stock); 
            printf("------------------------------\n"); 
        } 
    } 
} 

void search_by_code(int total_registrations, PRODUCTS list[]) { 
    char search_code[15]; 
    if(total_registrations == 0) { 
        printf("No product codes registered in the system!\n"); 
        return; 
    } 
    printf("Enter the code: "); 
    scanf(" %14[^\n]", search_code); 
    
    int index = find_index_by_code(search_code, total_registrations, list); 
    if(index != -1) { 
        printf("|--PRODUCT FOUND!--|\n"); 
        printf("NAME: %s.\n", list[index].name); 
        printf("CODE: %s.\n", list[index].code); 
        printf("PRICE: %.2f.\n", list[index].price); 
        printf("IN STOCK: %d.\n", list[index].stock); 
    } else { 
        printf("Code not found...\n"); 
    } 
} 

void update_product_stock(int total_registrations, PRODUCTS list[]) { 
    char search_code[15]; 
    if(total_registrations == 0) { 
        printf("No products registered to update!\n"); 
        return; 
    } 
    printf("Enter the code of the product you want to edit: "); 
    scanf(" %14[^\n]", search_code); 
    int index = find_index_by_code(search_code, total_registrations, list); 
    if(index != -1) { 
        printf("product-> %s\n", list[index].name); 
        printf("Enter the new stock value: "); 
        scanf("%d", &list[index].stock); 
        printf("Stock value updated!\n"); 
        return; 
    } else { 
        printf("Code not found!!"); 
    } 
} 

void update_price_status(int total_registrations, PRODUCTS list[]) { 
    char search_code[15]; 
    if(total_registrations == 0) { 
        printf("No products registered to update price!\n"); 
        return; 
    } 
    printf("Enter the code of the product you want to change price: "); 
    scanf(" %14[^\n]", search_code); 
    int index = find_index_by_code(search_code, total_registrations, list); 
    if(index != -1) { 
        printf("product-> %s\n", list[index].name); 
        printf("Enter the new product price: "); 
        scanf("%f", &list[index].price); 
        printf("Product price updated!\n"); 
        return; 
    } else { 
        printf("Code not found!!"); 
    } 
} 

void delete_product(int *total_registrations, PRODUCTS list[]) { 
    char search_code[15]; 
    if(*total_registrations == 0) { 
        printf("No products registered to discontinue!\n"); 
        return; 
    } 
    printf("Enter the code of the product you want to remove from stock: "); 
    scanf(" %14[^\n]", search_code); 
    
    int index = find_index_by_code(search_code, *total_registrations, list); 
    if(index != -1) { 
        // Shifts all remaining items to the left to fill the gap and keep array contiguous
        for(int j = index; j < (*total_registrations) - 1; j++) { 
            list[j] = list[j + 1]; 
        } 
        // Decreases the counter since one active slot was freed
        (*total_registrations)--; 
        printf("Product removed successfully!\n"); 
        return; 
    } else { 
        printf("Code not found!!"); 
    } 
} 

void calculate_stock(int total_registrations, PRODUCTS list[]) { 
    char search_code[15]; 
    float calculate_stock_price = 0; 
    if(total_registrations == 0) { 
        printf("No products registered to calculate stock!\n"); 
        return; 
    } 
    printf("Enter the code of the product you want to calculate stock value: "); 
    scanf(" %14[^\n]", search_code); 
    int index = find_index_by_code(search_code, total_registrations, list); 
    if(index != -1) { 
        // Financial calculation: stock volume multiplied by individual price
        calculate_stock_price = (list[index].stock * list[index].price); 
        printf("The stock value of (%s) is (%.2f)-USD$.\n", list[index].name, calculate_stock_price); 
        return; 
    } else { 
        printf("Code not found!!"); 
    } 
} 

void exit_system() { 
    printf("Exiting system....\n"); 
} 

int main() { 
    // Static memory allocation: 300 entries reserved on the stack at compile time
    PRODUCTS list[MAX_REGISTRATIONS]; 
    int total_registrations = 0; 
    int option; 

    do { 
        printf("|----SYSTEM - INVENTORY CONTROL----|\n"); 
        printf("1 - Register product in the system.\n2 - List registered products.\n3 - Search by product code.\n4 - Update stock of a product.\n5 - Update price of a product.\n6 - Remove a product from stock.\n7 - Total stock value.\n0 - Exit system.\nUser response: "); 
        scanf(" %d", &option); 
        printf("\033[H\033[j"); // Clears the terminal screen

        switch(option) { 
            case 1: 
                register_products(&total_registrations, list); 
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
                update_price_status(total_registrations, list); 
                break; 
            case 6: 
                delete_product(&total_registrations, list); 
                break; 
            case 7: 
                calculate_stock(total_registrations, list); 
                break; 
            case 0: 
                exit_system(); 
                break; 
            default: 
                printf("Invalid option !!\n"); 
        } 
    } while(option != 0); 

    return 0; 
}
