#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int sum = 0;
    int num1, num2;
    char ch;
    char str1[100]; 
    char str2[100];
    bool valid;

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

    while ((ch = getc(fp)) != EOF)
    {
        str1[0] = '\0';
        str2[0] = '\0'; 
        num1 = 0;
        num2 = 0;
        valid = true;

        if (ch == 'm' && (ch = getc(fp)) == 'u' && (ch = getc(fp)) == 'l' && (ch = getc(fp)) == '(')
        {
            while ((ch = getc(fp)) != EOF)
            {
                if (ch == ',') 
                    break;
                if (isdigit(ch))
                    sprintf(str1, "%s%c", str1, ch);
                else 
                {
                    valid = false; 
                    break; 
                }
            }

            if (valid) 
            {
                while ((ch = getc(fp)) != EOF)
                {
                    if (ch == ')')
                        break;
                    if (isdigit(ch))
                        sprintf(str2, "%s%c", str2, ch); 
                    else 
                    {
                        valid = false; 
                        break; 
                    }
                }
            }

            if (valid && str1[0] != '\0' && str2[0] != '\0')
            {
                num1 = atoi(str1);
                num2 = atoi(str2);
                sum += (num1 * num2);
            }
        }
    }
    fclose(fp); 
    printf("sum: %d\n", sum);
}

