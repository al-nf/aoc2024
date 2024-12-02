#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int i, inp, k, sum, diff1, diff2;


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

    while (fscanf(fp, "%d", &inp) != EOF)
    {
        if (inp == EOL)
        {
            
        }
    }
    printf("sum: %lld\n", sum);
}
