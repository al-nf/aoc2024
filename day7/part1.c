#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NUMBERS 100

unsigned long long evaluate_expression(int numbers[], char operators[], int n) 
{
    unsigned long long result = numbers[0];
    for (int i = 0; i < n - 1; i++) 
    {
        if (operators[i] == '+') 
        {
            result += numbers[i + 1];
        } 
        else if (operators[i] == '*') 
        {
            result *= numbers[i + 1];
        }
    }
    return result;
}

unsigned long long find_combinations_count(int target, int numbers[], int n) 
{
    int num_operators = n - 1;
    int num_combinations = 1 << num_operators;
    char operators[MAX_NUMBERS];
    unsigned long long count = 0;

    for (int mask = 0; mask < num_combinations; mask++) 
    {
        for (int i = 0; i < num_operators; i++) 
        {
            operators[i] = (mask & (1 << i)) ? '*' : '+';
        }

        unsigned long long result = evaluate_expression(numbers, operators, n);

        if (result == target) 
        {
            count++;
        }
    }

    return count;
}

int main(int argc, char *argv[]) 
{
    unsigned long long sum = 0;
    
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) 
    {
        return EXIT_FAILURE;
    }

    char line[1028];
    while (fgets(line, sizeof(line), fp)) 
    {
        int target, numbers[MAX_NUMBERS], n = 0;

        char *token = strtok(line, ":");
        target = atoi(token);

        token = strtok(NULL, " ");
        while (token != NULL && n < MAX_NUMBERS) 
        {
            numbers[n++] = atoi(token); 
            token = strtok(NULL, " ");
        }

        unsigned long long valid_combinations = find_combinations_count(target, numbers, n);
        
        if (valid_combinations > 0) 
        {
            sum += target;
        }
    }

    fclose(fp);
    printf("Total calibration result: %llu\n", sum);
}
