#include "stock.h"

/* Clears input streaming buffers to prevent hanging characters */
void clear_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Validates if the warehouse collection is completely empty */
bool empty_stock(const int total_registrations) {
    return (total_registrations == 0);
}

/* Sequentially scans the collection array matching unique item codes */
int find_product_by_code(const char *code, const int total_registrations, const PRODUCTS list[]) {
    for(int i = 0; i < total_registrations; i++) {
        if(strcmp(list[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

/* Inserts item data with automated dynamic block expansion triggers */
void register_products(int *total_registrations, int *current_capacity, PRODUCTS **list) {
    if(*total_registrations >= *current_capacity) {
        int new_capacity = (*current_capacity) * GROWTH_FACTOR;
        PRODUCTS *temp_list = (PRODUCTS *) realloc(*list, new_capacity * sizeof(PRODUCTS));
        
        if(temp_list == NULL) {
            printf("\nSystem error: Failed to reallocate memory! Storage is full.\n");
            return;
        }
        
        *list = temp_list;
        *current_capacity = new_capacity;
        printf("\n[System Notice] Storage capacity automatically expanded to %d slots.\n", *current_capacity);
    }
    
    char temporary_code[MAX_CODE];
    printf("|--PRODUCT TO BE REGISTED--| - (%d)\n", (*total_registrations) + 1);
    printf("CODE: ");
    scanf(" %" STR(14) "[^\n]", temporary_code);
    clear_buffer();
    
    if(find_product_by_code(temporary_code, *total_registrations, *list) != -1) {
        printf("\n Code rejected! Code already registered in the system!\n"); 
        return;
    }
    
    strncpy((*list)[*total_registrations].code, temporary_code, MAX_CODE - 1);
    (*list)[*total_registrations].code[MAX_CODE - 1] = '\0';
    
    printf("NAME: ");
    scanf(" %" STR(29) "[^\n]", (*list)[*total_registrations].name);
    clear_buffer();
    
    printf("PRICE: ");
    scanf("%f", &(*list)[*total_registrations].price);
                
    printf("IN STOCK: ");
    scanf("%d", &(*list)[*total_registrations].stock);
    clear_buffer();
    
    printf("PACKAGING UNIT: ");
    scanf(" %" STR(29) "[^\n]", (*list)[*total_registrations].packaging_unit);
    clear_buffer();
    
    (*total_registrations)++;
    printf("\nRegistration completed successfully!\n"); 
    
    /* Automatically save data to file upon change */
    save_to_file(*total_registrations, *current_capacity, *list);
}

/* Iterates across storage boundaries rendering formatted elements */
void list_products(const int total_registrations, const PRODUCTS list[]) {
    if(empty_stock(total_registrations)) {
        printf("No products registered in the system!\n"); 
        return;
    } else {
        printf("     |--REGISTERED PRODUCTS--| - (%d)\n", total_registrations); 
       
        for(int i = 0; i  %s\n", list[product].name); 
        printf("Enter the new stock value: "); 
        scanf("%d", &list[product].stock); 
        printf("stock value updated!\n"); 
        
        /* Save state updates after item field mutations */
        save_to_file(total_registrations, INITIAL_CAPACITY, list);
        return; 
    } else {
        printf("Code not found!!\n");
        return; 
    }
}

/* Modifies financial evaluation units for matching items */
void update_product_price(int total_registrations, PRODUCTS list[]) {
    char search_code[MAX_CODE];
    
    if(empty_stock(total_registrations)) {
        printf("No products registered to update price!\n"); 
        return;
    }
    
    printf("Enter the code of the product you want to edit: ");  
    scanf(" %" STR(14) "[^\n]", search_code);
    clear_buffer();
    
    int product = find_product_by_code(search_code, total_registrations, list);
    if(product != -1) { 
        printf("product-> %s\n", list[product].name); 
        printf("Enter the new product price: "); 
        scanf("%f", &list[product].price); 
        clear_buffer();
        printf("Product price updated!\n"); 
        
        /* Save state updates after item field mutations */
        save_to_file(total_registrations, INITIAL_CAPACITY, list);
        return; 
    } else { 
        printf("Code not found!!\n"); 
        return;
    } 
}

/* Deletes an array entry and shifts trailing elements left */
void delete_product(int *total_registrations, PRODUCTS list[]) {
    char search_code[MAX_CODE];
    
    if(empty_stock(*total_registrations)) {
        printf("No products registered to discontinue!\n"); 
        return; 
    }
    
    printf("Enter the code of the product you want to remove from stock: "); 
    scanf(" %" STR(14) "[^\n]", search_code);
    clear_buffer();
    
    int product = find_product_by_code(search_code, *total_registrations, list);
    if(product != -1) {
        for(int j = product; j < (*total_registrations) - 1; j++) {
            list[j] = list[j + 1];
        }
        (*total_registrations)--;
        printf("Product removed successfully!\n");
        
        /* Save modified state immediately following removal */
        save_to_file(*total_registrations, INITIAL_CAPACITY, list);
    } else {
        printf("Code not found!!\n");
        return;
    }
}

/* Compiles a localized product asset summary value (price * stock) */
void calculete_only_product_stock(const int total_registrations, const PRODUCTS list[]) {
    char search_code[MAX_CODE];
    float calculate_stock_price = 0;
    
    if(empty_stock(total_registrations)) {
        printf("No products registered to calculate stock!\n"); 
        return;
    }
    
    printf("Enter the code of the product you want to calculate stock value of one product: "); 
    scanf(" %" STR(14) "[^\n]", search_code); 
    clear_buffer();
    
    int product = find_product_by_code(search_code, total_registrations, list);
    if(product != -1) {
        calculate_stock_price = (list[product].stock * list[product].price); 
        printf("The stock value of (%s) is (%.2f) - USD$.\n", list[product].name, calculate_stock_price);
    } else {
        printf("Code not found!!\n");
        return;
    }
}

/* Tallies complete compound evaluation across all warehouse assets */
void calculete_full_stock(const int total_registrations, const PRODUCTS list[]) {
    if(empty_stock(total_registrations)) {
        printf("No products registered to calculate stock!\n"); 
        return;
    }
    
    float total_value = 0;
    for(int i = 0; i < total_registrations; i++) {
        total_value += (list[i].stock * list[i].price);
    }
    
    printf("The total economic value of the entire warehouse is: (%.2f) - USD$.\n", total_value);
}

/* Wipes the collection clean and drops capacity to starting scale */
void clear_stock(int *total_registrations, int *current_capacity, PRODUCTS **list) {
    if (empty_stock(*total_registrations)) {
        printf("Stock is already empty!\n");
        return;
    }
    
    PRODUCTS *temp_list = (PRODUCTS *) realloc(*list, INITIAL_CAPACITY * sizeof(PRODUCTS));
    if (temp_list != NULL) {
        *list = temp_list;
    }
    
    *total_registrations = 0;
    *current_capacity = INITIAL_CAPACITY;
    printf("All active records have been cleared. Warehouse storage reset!\n");
    
    /* Synchronize the reset storage back to the file system */
    save_to_file(*total_registrations, *current_capacity, *list);
}

/* Performs critical memory disposal tracking on user exit operations */
void exit_system(PRODUCTS *list) {
    printf("press ENTER to exit the menu....\n");
    clear_buffer();
    free(list); /* Securely frees allocated array space before process termination */
    exit(EXIT_SUCCESS);
}

/* Writes active metrics and dynamic struct arrays into a secure binary format */
void save_to_file(const int total_registrations, const int current_capacity, const PRODUCTS list[]) {

FILE *file = fopen("inventory.dat", "wb");
if (file == NULL){
printf("[Storage Alert] Failed to open system data layer file for writing!\n");
return;
}

fwrite(&total_registrations, sizeof(int), 1, file);
fwrite(&current_capacity, sizeof(int), 1, file);

if (total_registrations > 0){
fwrite(list, sizeof(PRODUCTS), total_registrations, file);
}

fclose(file);
}
/* Reconstructs historical runtime configurations directly from local disk storage */
void load_from_file(int *total_registrations, int *current_capacity, PRODUCTS **list){
FILE file = fopen("inventory.dat", "rb");
if (file == NULL){
/ File doesn't exist yet, which is normal for first execution runs */
return;
}

fread(total_registrations, sizeof(int), 1, file);
fread(current_capacity, sizeof(int), 1, file);

if (*total_registrations > 0){
PRODUCTS *temp_list = (PRODUCTS *) realloc(*list, (*current_capacity) * sizeof(PRODUCTS));
if (temp_list != NULL){
*list = temp_list;
fread(*list, sizeof(PRODUCTS), *total_registrations, file);
printf("[Storage System] Restored %d products successfully from persistent storage.\n", *total_registrations);
}
else{
printf("[Critical Recovery Error] Failed allocating memory heap for file extraction!\n");
*total_registrations = 0;
*current_capacity = INITIAL_CAPACITY;
  }
}
fclose(file);
}
