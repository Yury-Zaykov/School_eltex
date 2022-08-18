#pragma once

//-----------------------------------------------------------------------------------
//                              ОПРЕДЕЛЕНИЕ СПИСКА
//-----------------------------------------------------------------------------------
typedef struct list
{
    int val;                    // значение элемента (хранимые данные)                   

    struct list* next;          // единственный указатель или

    //struct list* prev;        // два указателя или

    //struct list* links[10];   // ограниченное количество указателей (не больше 10) или

    //struct list** plinks;     // произвольное количество указателей (внешний МУ)
} list;
//-----------------------------------------------------------------------------------
//                      ОПРЕДЕЛЕНИЕ БИНАРНОГО ДЕРЕВА ПОИСКА
//-----------------------------------------------------------------------------------
typedef struct tree
{
    int val;                    
    struct tree* left;
    struct tree* right;
} tree;
//-----------------------------------------------------------------------------------
//                                  ФУНКЦИИ СПИСКА 
//-----------------------------------------------------------------------------------
list* push_to_head(list* lst_h, int data);

list* push_to_tail(list* lst_t, int data);

void push_to_cell(list* lst_c, unsigned int cell, int data);

list* pop_to_head(list* lst_h);

void pop_to_tail(list* lst_t);

void pop_to_cell(list* lst_c, unsigned int cell);

int edit_head(list* lst_h, int data);

int edit_tail(list* lst_t, int data);

int edit_cell(list* lst_c, int cell, int data);

void sortUp_list(list* lst);

void sortDown_list(list* lst);

list* create_list();

void print_list_head(list* lst);

void print_list_tail(list* lst);

void free_list(list* lst);
//-----------------------------------------------------------------------------------
//                          ФУНКЦИИ БИНАРНОГО ДЕРЕВА
//-----------------------------------------------------------------------------------
tree* create_tree(int root);

void push_tree(tree* tr_p, int data);

//-----------------------------------------------------------------------------------