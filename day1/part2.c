#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int ss(int *data, int stuff)
{
    int sum = 0; 
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
    {
        if (data[i] == stuff)
            sum++;
    }
    return sum;
}
int main(int argc, char *argv[])
{
    FILE *fp;
    int i, inp, k;
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
    k = 0;
    while (fscanf(fp, "%d", &inp) != EOF)
    {
        if (i%2 == 0)
        {
            data1[k] = inp;
        }
        else 
        {
            data2[k] = inp;
            k++;
        }
        i++;
    }

    /*
    int compare(const void *a, const void *b) 
    {
        return *(int*)a - *(int*)b;
    }

    qsort(data1, k, sizeof(int), compare);
    qsort(data2, k, sizeof(int), compare);
    */

    sum = 0;

    for (int j = 0; j < k; j++)
    {
        sum += ss(data2, data1[j]);
    }

    printf("sum: %lld\n", sum);
}
