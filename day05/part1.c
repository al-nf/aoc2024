#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_PAGES 100

typedef struct node 
{
    int data;
    struct node *next;
} NODE;

typedef struct list 
{
    NODE *head;
} LIST;

static LIST *createList()
{
    LIST *lp = malloc(sizeof(LIST)); assert(lp != NULL);
    NODE *dummy = malloc(sizeof(NODE)); assert(dummy != NULL);
    lp->head = dummy;
    lp->head->next = lp->head;
    return lp;
}

static void addNode(LIST *lp, int data)
{
    NODE *np = malloc(sizeof(NODE)); assert(np != NULL);
    np->data = data;
    np->next = lp->head->next;
    lp->head->next = np;
}

static void destroyList(LIST *lp)
{
    NODE *np = lp->head->next;
    while (np != lp->head) 
    {
        NODE *temp = np;
        np = np->next;
        free(temp);
    }
    free(lp->head);
    free(lp);
}

static int isValid(int *update, int size, LIST **data)
{
    int pos[MAX_PAGES];
    for (int i = 0; i < MAX_PAGES; i++) 
    {
        pos[i] = -1;
    }

    for (int i = 0; i < size; i++) 
    {
        pos[update[i]] = i;
    }

    for (int i = 0; i < MAX_PAGES; i++) 
    {
        NODE *np = data[i]->head->next;
        while (np != data[i]->head) 
        {
            int page1 = i;
            int page2 = np->data;
            if (pos[page1] != -1 && pos[page2] != -1 && pos[page1] > pos[page2]) 
            {
                return 0; 
            }
            np = np->next;
        }
    }

    return 1;
}

static int findMiddlePage(int *update, int size)
{
    if (size == 0) 
    {
        return -1;
    }
    return update[size / 2];
}

int main(int argc, char *argv[]) 
{
    FILE *fp1, *fp2;
    int sum = 0;
    LIST **data;

    if (argc != 3) 
    {
        exit(EXIT_FAILURE);
    }

    if ((fp1 = fopen(argv[1], "r")) == NULL) 
    {
        exit(EXIT_FAILURE);
    }

    if ((fp2 = fopen(argv[2], "r")) == NULL) 
    {
        fclose(fp1);
        exit(EXIT_FAILURE);
    }

    data = malloc(sizeof(LIST*) * MAX_PAGES); assert(data != NULL);
    for (int i = 0; i < MAX_PAGES; i++) 
    {
        data[i] = createList();
    }

    int j, k;
    while (fscanf(fp1, "%d|%d", &j, &k) != EOF) 
    {
        if (j < 0 || j >= MAX_PAGES || k < 0 || k >= MAX_PAGES) 
        {
            continue;
        }
        addNode(data[j], k);
    }

    char line[256];
    while (fgets(line, sizeof(line), fp2)) 
    {
        int update[MAX_PAGES];
        int size = 0;
        char *token = strtok(line, ",");
        while (token != NULL && size < MAX_PAGES) 
        {
            update[size++] = atoi(token);
            token = strtok(NULL, ",");
        }

        if (size > 0 && isValid(update, size, data)) 
        {
            int midPage = findMiddlePage(update, size);
            if (midPage != -1) 
            {
                sum += midPage;
            }
        }
    }

    fclose(fp1);
    fclose(fp2);

    for (int i = 0; i < MAX_PAGES; i++) 
    {
        destroyList(data[i]);
    }
    free(data);

    printf("sum: %d\n", sum);
}
