#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ROWS 140

int main(int argc, char *argv[])
{
    FILE *fp;
    int sum = 0;
    int arr[ROWS][ROWS];

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

    // parse data into 2d array
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            arr[i][j] = getc(fp);
        }
        getc(fp); // pass over the newline
    }

    // this is legitimately stupid
    for (int i = 1; i < ROWS-1; i++)
    {
        for (int j = 1; j < ROWS-1; j++)
        {
            if (arr[i][j] == 'A')
            {
                if ((arr[i-1][j-1] == 'M' && arr[i+1][j+1] == 'S') || (arr[i-1][j-1] == 'S' && arr[i+1][j+1] == 'M')) // check diagonal
                {
                    if ((arr[i-1][j+1] == 'M' && arr[i+1][j-1] == 'S') || (arr[i-1][j+1] == 'S' && arr[i+1][j-1] == 'M')) // check antidiagonal
                        sum++;
                }
            }
        }
    }

    /* DEBUG
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < ROWS; j++) {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
    */
    fclose(fp); 
    printf("sum: %d\n", sum);
}

