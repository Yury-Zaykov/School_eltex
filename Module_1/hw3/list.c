#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h"
//-----------------------------------------------------------------------------------
//                    ÔÓÍÊÖÈÈ ÄÎÁÀÂËÅÍÈß ÝËÅÌÅÍÒÎÂ Â ÑÏÈÑÎÊ
//-----------------------------------------------------------------------------------
list* push_to_head(list* lst_h, int data)
{
    
    list* tmp = (list*)malloc(sizeof(list));

    if (tmp == NULL)
    {
        printf("\n\rFail recording in list!");
        free(tmp);
        return lst_h;
    }

    tmp->val = data;

    tmp->next = lst_h;

    return tmp;
}

list* push_to_tail(list* lst_t, int data)
{
    list* rt = lst_t;
    list* tmp = (list*)malloc(sizeof(list));

    if (tmp == NULL)
    {
        printf("\n\rFail recording in list!");
        free(tmp);
        return lst_t;
    }

    if (lst_t == NULL)
    {
        tmp->val = data;

        tmp->next = lst_t;

        return tmp;
    }

    while (lst_t->next != NULL)
    {
        lst_t = lst_t->next;
    }

    tmp->val = data;

    tmp->next = NULL;

    lst_t->next = tmp;

    return rt;
}

void push_to_cell(list* lst_c, unsigned int cell, int data)
{
    if (cell < 1)
    {
        printf("Fail recording in list");
        return;
    }

    list* tmp = (list*)malloc(sizeof(list));

    if (tmp == NULL)
    {
        printf("\n\rFail recording in list!");
        free(tmp);
        return;
    }

    for (unsigned int i = 0; i + 1 < cell && lst_c != NULL; i++)
    {
        lst_c = lst_c->next;
    }

    if (lst_c == NULL)
    {
        printf("\n\rFail recording in list!");
        free(tmp);
        return;
    }

    tmp->val = data;

    tmp->next = lst_c->next;

    lst_c->next = tmp;
}
//-----------------------------------------------------------------------------------
//                          ÔÓÍÊÖÈÈ ÓÄÀËÅÍÈß ÝËÅÌÅÍÒÎÂ ÑÏÈÑÊÀ
//-----------------------------------------------------------------------------------
list* pop_to_head(list* lst_h)
{
    list* tmp = lst_h->next;

    free(lst_h);

    return tmp;
}

void pop_to_tail(list* lst_t)
{
    while (lst_t->next->next != NULL)
    {
        lst_t = lst_t->next;
    }

    free(lst_t->next);

    lst_t->next = NULL;
}

void pop_to_cell(list* lst_c, unsigned int cell)
{
    if (cell < 1)
    {
        printf("Fail delete the cell in list");
        return;
    }

    for (unsigned int i = 0; i + 1 < cell && lst_c != NULL; i++)
    {
        lst_c = lst_c->next;
    }

    if (lst_c == NULL)
    {
        printf("\n\rFail delete the cell in list!");
        return;
    }

    list* tmp = lst_c->next->next;

    free(lst_c->next);

    lst_c->next = tmp;
}
//-----------------------------------------------------------------------------------
//                              ÔÓÍÊÖÈÈ ÐÅÄÀÊÒÈÐÎÂÀÍÈß ÑÏÈÑÊÀ 
//-----------------------------------------------------------------------------------
int edit_head(list* lst_h, int data)
{
    int tmp = lst_h->val;
    lst_h->val = data;
    return tmp;
}

int edit_tail(list* lst_t, int data)
{
    while (lst_t->next != NULL)
    {
        lst_t = lst_t->next;
    }

    int tmp = lst_t->val;
    lst_t->val = data;
    return tmp;
}

int edit_cell(list* lst_c, int cell, int data)
{
    for (unsigned int i = 0; i + 1 < cell && lst_c != NULL; i++)
    {
        lst_c = lst_c->next;
    }

    if (lst_c == NULL)
    {
        printf("\n\rFail edit the cell in list!");
        return;
    }

    int tmp = lst_c->val;
    lst_c->val = data;
    return tmp;
}
//-----------------------------------------------------------------------------------
//                                  ÑÎÐÒÈÐÎÂÊÀ ÑÏÈÑÊÀ
//-----------------------------------------------------------------------------------
void sortUp_list(list* lst)
{
    list* cl1 = lst, *cl2, *min;
    int cnt = 0;
    int tmp;


    while (cl1 != NULL)
    {
        min = cl1;
        cl2 = cl1;
        while (cl2 != NULL)
        {
            if (min->val > cl2->val)
            {
                min = cl2;
            }
            cl2 = cl2->next;
        }
        tmp = cl1->val;
        cl1->val = min->val;
        min->val = tmp;

        cl1 = cl1->next;
    }
}

void sortDown_list(list* lst)
{
    list* cl1 = lst, * cl2, * max;
    int cnt = 0;
    int tmp;

    while (cl1 != NULL)
    {
        max = cl1;
        cl2 = cl1;
        while (cl2 != NULL)
        {
            if (max->val < cl2->val)
            {
                max = cl2;
            }
            cl2 = cl2->next;
        }
        tmp = cl1->val;
        cl1->val = max->val;
        max->val = tmp;

        cl1 = cl1->next;
    }
}

//-----------------------------------------------------------------------------------
//                                  ÑÎÇÄÀÍÈÅ ÑÏÈÑÊÀ
//-----------------------------------------------------------------------------------
list* create_list()
{
    list* lst = NULL;
    return lst;
}
//-----------------------------------------------------------------------------------
//                          ÂÛÂÎÄ ÝËÅÌÅÍÒÎÂ ÑÏÈÑÊÀ Â ÊÎÍÑÎËÜ
//-----------------------------------------------------------------------------------
void print_list_head(list* lst)
{
    printf("\n\rList contains(head): ");
    //list* tmp;
    while (lst != NULL)
    {
        printf("%d ", lst->val);
        lst = lst->next;
    }
}



//-----------------------------------------------------------------------------------
//                              ÓÄÀËÅÍÈÅ ÝËÅÌÅÍÒÎÂ ÑÏÈÑÊÀ
//-----------------------------------------------------------------------------------
void free_list(list* lst)
{
    list* tmp;
    while (lst != NULL)
    {
        tmp = lst->next;
        free(lst);
        lst = tmp;
    }
}
//-----------------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------------
tree* create_tree(int root)
{
    tree* tr = (tree*)malloc(sizeof(tree));
    tr->left = NULL;
    tr->right = NULL;
    tr->val = root;
    return tr;
}

void push_tree(tree* tr_p, int data)
{
    tree* first = tr_p;
    
     while (!(data >= tr_p->val && tr_p->right == NULL) && !(data < tr_p->val && tr_p->left == NULL))
    {
        if (data > tr_p->val)
        {
            tr_p = tr_p->right;
        }
        else
        {
            tr_p = tr_p->left;
        }
    }

    tree* tmp = (tree*)malloc(sizeof(tree));
    if (tmp == NULL)
    {
        printf("\n\rFail recording in list!");
        free(tmp);
        return;
    }
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->val = data;

    if (data >= tr_p->val)
    {
        tr_p->right = tmp;
    }
    else
    {
        tr_p->left = tmp;
    }
}





//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%