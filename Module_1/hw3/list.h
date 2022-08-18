#pragma once

//-----------------------------------------------------------------------------------
//                              ����������� ������
//-----------------------------------------------------------------------------------
typedef struct list
{
    int val;                    // �������� �������� (�������� ������)                   

    struct list* next;          // ������������ ��������� ���

    //struct list* prev;        // ��� ��������� ���

    //struct list* links[10];   // ������������ ���������� ���������� (�� ������ 10) ���

    //struct list** plinks;     // ������������ ���������� ���������� (������� ��)
} list;
//-----------------------------------------------------------------------------------
//                      ����������� ��������� ������ ������
//-----------------------------------------------------------------------------------
typedef struct tree
{
    int val;                    
    struct tree* left;
    struct tree* right;
} tree;
//-----------------------------------------------------------------------------------
//                                  ������� ������ 
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
//                          ������� ��������� ������
//-----------------------------------------------------------------------------------
tree* create_tree(int root);

void push_tree(tree* tr_p, int data);

//-----------------------------------------------------------------------------------