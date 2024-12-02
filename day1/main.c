#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int i, inp;
    int data1[5000];
    int data2[5000];
    unsigned long long sum;

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

    i = 0; 
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

    int compare(const void *a, const void *b) 
    {
        return *(int*)a - *(int*)b;
    }
    qsort(data1, i-1, 5000, compare);
    qsort(data2, i-1, 5000, compare);
    sum = 0;
    for (int j = 0; j < i-1; j++)
    {

        sum += abs(data2[j] - data1[j]);
    }

    printf("sum: %lld\n", sum);
}
