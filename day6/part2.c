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

void move(enum dir direction, int *x, int *y) {
    switch (direction) {
        case u: (*y)--; break;
        case r: (*x)++; break;
        case d: (*y)++; break; 
        case l: (*x)--; break;  
    }
}

bool causes_infinite_loop(char arr[ROWS][COLS], int start_x, int start_y, int obstacle_x, int obstacle_y) {
    enum dir direction = u;
    bool visited[ROWS][COLS] = {false};
    enum dir directionsVisited[ROWS][COLS] = {0}; 
    int current_x = start_x, current_y = start_y;

    arr[obstacle_y][obstacle_x] = '#';

    while (true) {
        int next_x = current_x, next_y = current_y;
        move(direction, &next_x, &next_y);

        if (next_y < 0 || next_y >= ROWS || next_x < 0 || next_x >= COLS) {
            break; 
        }

        if (arr[next_y][next_x] == '#') {
            direction = (enum dir)((direction + 1) % 4);
        } else {
            if (visited[next_y][next_x] && directionsVisited[next_y][next_x] == direction) {
                arr[obstacle_y][obstacle_x] = '.'; 
                return true;
            }

            current_x = next_x;
            current_y = next_y;

            if (!visited[current_y][current_x]) {
                visited[current_y][current_x] = true;
                directionsVisited[current_y][current_x] = direction;
            }
        }
    }

    arr[obstacle_y][obstacle_x] = '.'; 
    return false; 
}

int main(int argc, char *argv[]) {
    FILE *fp;
    char arr[ROWS][COLS];
    int guard_x = -1, guard_y = -1;
    int valid_positions_count = 0;

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
                guard_x = j;
                guard_y = i;
                arr[i][j] = '.';
            }
        }
        getc(fp); 
    }
    fclose(fp);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (arr[i][j] != '.' || (i == guard_y && j == guard_x)) {
                continue;
            }

            if (causes_infinite_loop(arr, guard_x, guard_y, j, i)) {
                valid_positions_count++;
            }
        }
    }

    printf("sum: %d\n", valid_positions_count);
    return 0;
}

