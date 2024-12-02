#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int i, inp, sum;
    int data1[2000];
    int data2[2000];

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
            data1[i] = inp;
        }
        else 
        {
            data2[i] = inp;
        }
        i++;
    }
    
    qsort(data1, i, 2000);
    qsort(data2, i, 2000);
    sum = 0;
    for (int j = 0; j < i; j++)
    {
        sum += abs(data2[i] - data1[i]);
    }

    printf("sum: %d\n", sum);
}
