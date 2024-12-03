#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

bool is_safe_report(int levels[], int n) {
    bool isIncreasing = false;
    bool isDecreasing = false;
    int linp, diff;

    linp = levels[0];
    for (int i = 1; i < n; i++) {
        diff = levels[i] - linp;

        if (diff > 3 || diff < -3) {
            return false;
        }

        if (diff > 0) {
            if (isDecreasing) return false;
            isIncreasing = true;
        }
        else if (diff < 0) {
            if (isIncreasing) return false;
            isDecreasing = true;
        }
        else {
            return false;
        }

        linp = levels[i];
    }

    return true;
}

bool can_be_safe_by_removing_one_level(int levels[], int n) {
    for (int i = 0; i < n; i++) {
        int new_levels[n - 1];
        int idx = 0;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                new_levels[idx++] = levels[j];
            }
        }

        if (is_safe_report(new_levels, n - 1)) {
            return true;
        }
    }

    return false;
}

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[MAX_LINE_LENGTH];
    int inp, linp, diff;
    int sum = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Cannot open file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // whoever made fgets needs to be viciously punished
    while (fgets(buffer, MAX_LINE_LENGTH, fp) != NULL) {
        int levels[MAX_LINE_LENGTH];
        int level_count = 0;

        char *ptr = buffer;
        while (sscanf(ptr, "%d", &inp) == 1) {
            levels[level_count++] = inp;

            // stupid pointer logic
            while (*ptr != '\0' && *ptr != ' ' && *ptr != '\n') {
                ptr++;
            }
            while (*ptr == ' ') {
                ptr++;
            }
        }

        if (is_safe_report(levels, level_count)) {
            sum++;
        }
        else if (can_be_safe_by_removing_one_level(levels, level_count)) {
            sum++;
        }
    }

    fclose(fp);
    printf("sum: %d\n", sum);
}

