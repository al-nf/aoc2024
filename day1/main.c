#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
    int data;
    struct node *next;
    struct node *prev;
} NODE;

typedef struct list
{
    int count;
    struct node *head;
} LIST;

void addLast(LIST *lp, int data)
{
    assert(lp != NULL);
    NODE *np = malloc(sizeof(NODE)); assert(np != NULL);
    np->data = data;
    np->next = lp->head;
    np->prev = lp->head->prev;
    lp->head->prev = np;
    ++(lp->count);
}

LIST *createList()
{
    LIST *lp = malloc(sizeof(LIST)); assert(lp != NULL);
    lp->count = 0;
    
    NODE *dummy = malloc(sizeof(NODE)); assert(dummy != NULL);
    lp->head = dummy;
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    
    return lp;
}

void destroyList(LIST *lp)
{
    assert(lp != NULL);
    NODE *nDel = lp->head->prev;
    while(nDel->prev != lp->head)
    {
        nDel = nDel->prev;
        free(nDel->next);
    }
    free(lp->head);
    free(lp);
}

int main(int argc, char *argv[])
    FILE *fp;
    
