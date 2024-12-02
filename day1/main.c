#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node 
{
    int data;
    struct node *next;
    struct node *prev;
} NODE;

typedef struct list
{
    int count;
    NODE *head;
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
    lp->head->next = dummy;
    lp->head->prev = dummy;
    
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
{
    FILE *fp;
    LIST *list1 = createList();
    LIST *list2 = createList();
    int i, inp, sum;

    if (argc != 2)
    {
        fprintf(stderr, "????\n");
        exit(EXIT_FAILURE);
    }
    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "cannot open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    assert(fp != NULL);

    i = 0; // iterator for mod idk
    while (fscanf(fp, "%d", &inp) != EOF)
    {
        if (i%2 == 0)
        {
            addLast(list1, inp);
        }
        else 
        {
            addLast(list2, inp);
        }
        i++;
    }
    
    sum = 0;
    NODE *node1 = list1->head->next;
    NODE *node2 = list2->head->next;
    for (int i = 0; i < list2->count; i++)
    {
        sum += abs((node2->data) - (node1->data));
        node1 = node1->next;
        node2 = node2->next;
    }

    destroyList(list1);
    destroyList(list2);

    printf("sum: %d", sum);
}
