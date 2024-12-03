#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[])
{
    FILE *fp;
    char buffer[MAX_LINE_LENGTH];
    int inp, linp, diff;
    int sum = 0;
    bool isFirst, good, isIncreasing, isDecreasing;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Cannot open file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // whoever made fgets needs to be viciously punished
    while (fgets(buffer, MAX_LINE_LENGTH, fp) != NULL)
    {
        char *ptr = buffer; 
        good = true;
        isFirst = true;
        isIncreasing = false;
        isDecreasing = false;

        while (sscanf(ptr, "%d", &inp) == 1)
        {
            if (isFirst)
            {
                linp = inp; 
                isFirst = false;
            }
            else
            {
                diff = inp - linp;

                printf("inp: %d, linp: %d, diff: %d\n", inp, linp, diff);

                if (diff > 3 || diff < -3)
                {
                    good = false;
                    break;
                }

                if (diff > 0)
                {
                    if (isDecreasing)
                    {
                        good = false;
                        break;
                    }
                    isIncreasing = true;
                }
                else if (diff < 0) 
                {
                    if (isIncreasing)
                    {
                        good = false;
                        break;
                    }
                    isDecreasing = true;
                }
                else
                {
                    good = false;
                    break;
                }

                linp = inp;
            }

            // stupid pointer logic
            while (*ptr != '\0' && *ptr != ' ' && *ptr != '\n') 
                ptr++;
            while (*ptr == ' ')
                ptr++;
        }

        if (good && !isFirst) 
        {
            sum++;
        }

    }

    fclose(fp);
    printf("sum: %d\n", sum);
}

