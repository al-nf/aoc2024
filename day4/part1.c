#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Cannot open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    assert(fp != NULL);

    



    fclose(fp); 
    printf("sum: %d\n", sum);
    return 0; 
}

