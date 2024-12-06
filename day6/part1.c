#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 130
#define COLS 130

enum dir {
    u = 0, 
    r = 1,
    d = 2,
    l = 3
};

// Moves the coordinates in the specified direction
void move(enum dir direction, int *x, int *y) {
    switch (direction) {
        case u: (*y)--; break;
        case r: (*x)++; break;
        case d: (*y)++; break; 
        case l: (*x)--; break;  
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    char arr[ROWS][COLS];
    bool visited[ROWS][COLS] = {0};
    int current[] = {0, 0}; 
    int sum = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            arr[i][j] = getc(fp);
            if (arr[i][j] == '^') {
                current[0] = j;
                current[1] = i;
                visited[i][j] = true;
                sum++;  
            }
        }
        getc(fp); 
    }
    fclose(fp);

    enum dir direction = u; 

    while (1) {
        int next[] = {current[0], current[1]};
        move(direction, &next[0], &next[1]);

        if (next[1] < 0 || next[1] >= ROWS || next[0] < 0 || next[0] >= COLS) {
            break;  
        }

        if (arr[next[1]][next[0]] == '#') {
            direction = (enum dir)((direction + 1) % 4);
        } else {
            current[0] = next[0];
            current[1] = next[1];

            if (!visited[current[1]][current[0]]) {
                visited[current[1]][current[0]] = true;
                sum++; 
            }
        }
    }

    printf("sum: %d\n", sum);
    return 0;
}

