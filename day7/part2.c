#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NUMBERS 100

unsigned long long evaluate_expression(unsigned long long numbers[], char operators[], unsigned long long n) 
{
    unsigned long long result = numbers[0];

    for (unsigned long long i = 0; i < n - 1; i++) 
    {
        if (operators[i] == '+') 
        {
            result += numbers[i + 1];
        } 
        else if (operators[i] == '*') 
        {
            result *= numbers[i + 1];
        }
        else if (operators[i] == '|')
        {
            unsigned long long temp = numbers[i + 1];
            unsigned long long power_of_ten = 1;

            while (temp > 0) 
            {
                power_of_ten *= 10;
                temp /= 10;
            }

            result = result * power_of_ten + numbers[i + 1];
        }
        else 
        {
            fprintf(stderr, "Unknown operator encountered: %c\n", operators[i]);
            exit(EXIT_FAILURE);
        }
    }

    return result;
}

unsigned long long find_combinations_count(unsigned long long target, unsigned long long numbers[], unsigned long long n) 
{
    if (n == 0) return 0; 

    int num_operators = n - 1;
    int num_combinations = 1 << (2 * num_operators); 
    char operators[MAX_NUMBERS - 1];
    unsigned long long count = 0;

    for (int mask = 0; mask < num_combinations; mask++) 
    {
        for (int i = 0; i < num_operators; i++) 
        {
            int op_index = (mask >> (2 * i)) & 0b11; 
            if (op_index == 0) 
            {
                operators[i] = '+'; // 00
            } 
            else if (op_index == 1) 
            {
                operators[i] = '*'; // 01
            } 
            else 
            {
                operators[i] = '|'; // 10 
            }
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
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char line[1028];
    while (fgets(line, sizeof(line), fp)) 
    {
        unsigned long long target, numbers[MAX_NUMBERS], n = 0;

        char *token = strtok(line, ":");
        if (token != NULL) 
        {
            target = strtoull(token, NULL, 10);
        } 
        else 
        {
            continue; 
        }

        token = strtok(NULL, " ");
        while (token != NULL && n < MAX_NUMBERS) 
        {
            numbers[n++] = strtoull(token, NULL, 10); 
            token = strtok(NULL, " ");
        }

        unsigned long long valid_combinations = find_combinations_count(target, numbers, n);
        
        if (valid_combinations > 0) 
        {
            sum += target;
        }
    }

    fclose(fp);
    printf("sum: %llu\n", sum);
}

