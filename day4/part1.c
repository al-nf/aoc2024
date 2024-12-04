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
        getc(fp); // clears the newline
    }

    // HORIZONTAL
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < ROWS-3; j++)
        {
            if (arr[i][j] == 'X' && arr[i][j+1] == 'M' && arr[i][j+2] == 'A' && arr[i][j+3] == 'S')
            {
                sum++;
            }
            if (arr[i][j] == 'S' && arr[i][j+1] == 'A' && arr[i][j+2] == 'M' && arr[i][j+3] == 'X')
            {
                sum++;
            }
        }
    }

    // VERTICAL
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < ROWS-3; j++)
        {
            if (arr[j][i] == 'X' && arr[j+1][i] == 'M' && arr[j+2][i] == 'A' && arr[j+3][i] == 'S')
            {
                sum++;
            }
            if (arr[j][i] == 'S' && arr[j+1][i] == 'A' && arr[j+2][i] == 'M' && arr[j+3][i] == 'X')
            {
                sum++;
            }
        }
    }

    // DIAGONAL
    for (int i = 0; i < ROWS - 3; i++)
    {
        for (int j = 0; j < ROWS - 3; j++) 
        {
            if (arr[i][j] == 'X' && arr[i+1][j+1] == 'M' && arr[i+2][j+2] == 'A' && arr[i+3][j+3] == 'S')
            {
                sum++;  
            }
            if (arr[i][j] == 'S' && arr[i+1][j+1] == 'A' && arr[i+2][j+2] == 'M' && arr[i+3][j+3] == 'X')
            {
                sum++;  
            }
        }
    }

    // ANTIDIAGONAL
    for (int i = 3; i < ROWS; i++)
    {
        for (int j = 0; j < ROWS - 3; j++)
        {
            if (arr[i][j] == 'X' && arr[i-1][j+1] == 'M' && arr[i-2][j+2] == 'A' && arr[i-3][j+3] == 'S')
            {
                sum++;  
            }
            if (arr[i][j] == 'S' && arr[i-1][j+1] == 'A' && arr[i-2][j+2] == 'M' && arr[i-3][j+3] == 'X')
            {
                sum++;  
            }
        }
    }

    fclose(fp); 
    printf("sum: %d\n", sum);
}

