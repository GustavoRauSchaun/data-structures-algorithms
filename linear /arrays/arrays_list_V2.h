#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdbool.h>

/* System Constraints and Sizing Parameters */
#define INITIAL_CAPACITY 5
#define GROWTH_FACTOR 2

#define MAX_CODE 15
#define MAX_NAME 30
#define MAX_PACKAGING_UNIT 30

/* Macro functions for dynamic string evaluation in scanf */
#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

/* Data structure definition for inventory items */
typedef struct {
    char name[MAX_NAME];
    char code[MAX_CODE];
    char packaging_unit[MAX_PACKAGING_UNIT];
    float price;
    int stock;
} PRODUCTS;

/* Utility and Validation Functions */
void clear_buffer(void);
bool empty_stock(const int total_registrations);
int find_product_by_code(const char *code, const int total_registrations, const PRODUCTS list[]);

/* Core Business Logic Functions */
void register_products(int *total_registrations, int *current_capacity, PRODUCTS **list);
void list_products(const int total_registrations, const PRODUCTS list[]);
void search_by_code(const int total_registrations, const PRODUCTS list[]);
void update_product_stock(const int total_registrations, PRODUCTS list[]);
void update_product_price(int total_registrations, PRODUCTS list[]);
void delete_product(int *total_registrations, PRODUCTS list[]);

/* Calculation and Reporting Functions */
void calculete_only_product_stock(const int total_registrations, const PRODUCTS list[]);
void calculete_full_stock(const int total_registrations, const PRODUCTS list[]);
void clear_stock(int *total_registrations, int *current_capacity, PRODUCTS **list);
void exit_system(PRODUCTS *list);

/* Persistence Mechanism Functions */
void save_to_file(const int total_registrations, const int current_capacity, const PRODUCTS list[]);
void load_from_file(int *total_registratio
