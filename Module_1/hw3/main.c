#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h"



int main()
{
    list* list1 = create_list();

    printf("\n\rRecord in head");

    for (int i = 0; i < 10; i++)
    {
        list1 = push_to_head(list1, i);
    }

    print_list_head(list1);

    printf("\n\n\rRecord in tail");

    for (int i = 1; i < 10; i++)
    {
        push_to_tail(list1, i);
    }

    print_list_head(list1);

    printf("\n\n\rRecord in cell");

    for (size_t i = 0; i < 2; i++)
    {
        push_to_cell(list1, 9, 0);
    }

    print_list_head(list1);

    printf("\n\n\rDelete head the cell");

    list1 = pop_to_head(list1);

    print_list_head(list1);

    printf("\n\n\rDelete tail the cell");

    pop_to_tail(list1);

    print_list_head(list1);

    printf("\n\n\rDelete the cell");

    pop_to_cell(list1, 9);

    print_list_head(list1);

    printf("\n\n\rEdit head");

    edit_head(list1, 18);

    print_list_head(list1);

    printf("\n\n\rEdit tail");

    edit_tail(list1, 18);

    print_list_head(list1);

    printf("\n\n\rEdit head");

    edit_cell(list1, 9, -50);
    edit_cell(list1, 10, -50);

    print_list_head(list1);

    free_list(list1);

    printf("\n\n\rList Delete\n");

    list* list2 = create_list();
    printf("\n\rList Create\n");

    printf("\n\rRecord rand in tail");

    srand(2);
    for (int i = 0; i < 20; i++)
    {
        list2 = push_to_tail(list2, rand()%100);
    }

    print_list_head(list2);

    printf("\n\nSort Up in list");

    sortUp_list(list2);

    print_list_head(list2);

    printf("\n\nSort Down in list");

    sortDown_list(list2);

    print_list_head(list2);

    free_list(list2);

    printf("\n\n\rList Delete\n");

    //---------------------------------------------------------------
    printf("\n\rTree Create\n");

    tree* tree1;
    tree1 = create_tree(100);

    printf("\n\rPush in tree\n");


    for (size_t i = 0; i < 20; i++)
    {
        push_tree(tree1, rand() % 200);
    }


    /*int n;
    printf("Enter size:");
    scanf("%d", &n);

    int* A = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        A[i] = i * 5;
        printf("A[%d]:%d\n\r", i, A[i]);
    }

    printf("\n\rAll ok");

    free(A);*/

    return 0;
}