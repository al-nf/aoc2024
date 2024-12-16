#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

#define ULL unsigned long long

using namespace std;

pair<int, int> getDir(char ch)
{
    switch (ch)
    {
        case '^':
            return make_pair(-1, 0);
        case '>':
            return make_pair(0, 1); 
        case 'v':
            return make_pair(1, 0); 
        case '<':
            return make_pair(0, -1);
    }
    return {0, 0};
}

void convertMap(vector<vector<char>>& a)
{
    vector<vector<char>> newMap;

    for (int i = 0; i < a.size(); i++)
    {
        vector<char> row;
        for (int j = 0; j < a[0].size(); j++)
        {
            switch (a[i][j])
            {
                case '#':
                {
                    row.push_back('#');
                    row.push_back('#');
                    break;
                }
                case 'O':
                {
                    row.push_back('[');
                    row.push_back(']');
                    break;
                }
                case '.':
                {
                    row.push_back('.');
                    row.push_back('.');
                    break;
                }
                case '@':
                {
                    row.push_back('@');
                    row.push_back('.');
                    break;
                }
            }
        }
        newMap.push_back(row);
    }
    a.assign(newMap.begin(), newMap.end());
}

bool isValid(int x, int y, const vector<vector<char>>& a)
{
    if (x >= 0 && x < a.size() && y >= 0 && y < a[0].size())
    {
        if (a[x][y] != '#')
        {
            return true;
        }
    }
    return false;

}

int boxTouchingTwoBoxes(const int& x, const int& y, const vector<vector<char>>& a, char dir)
{
    auto [dx, dy] = getDir(dir);
    int nx = x + dx;
    int ny = y + dy;
    int next = 0;
    char box = a[nx][ny];
    char opposite;
    if (box == '[')
    {
        next++;
        opposite = ']';
    }
    if (box == ']')
    {
        next--;
        opposite = '[';
    }
    

    // case -1: there are no boxes period
    if (!(isValid(nx, ny, a) && isValid(nx, ny+next, a)))
    {
        printf("PANIC!!!222\n");
        return -1;
    }
    // case 0: there are no boxes above
    if (isValid(nx+dx,ny+dy,a) && isValid(nx+dx,ny+dy+next,a) && a[nx+dx][ny+dy] == '.' && a[nx+dx][ny+dy+next] == '.')
    {
        printf("CASE 0 REACHED\n");
        return 0;
    }
    // case 1: there is one box down the middle
    if (isValid(nx+dx,ny+dy,a) && isValid(nx+dx,ny+dy+next,a) && a[nx+dx][ny+dy] == box && a[nx+dx][ny+dy+next] == opposite)
    {
        printf("CASE 1 REACHED\n");
        return 1;
    }
    // case 2: there are two boxes down the middle
    if (isValid(nx+dx, ny+dy-next, a) && isValid(nx+dx, ny+dy, a) && isValid(nx+dx, ny+dy+next, a) && isValid(nx+dx, ny+dy+(2*next), a) && a[nx+dx][ny+dy-next] == box && a[nx+dx][ny+dy] == opposite && a[nx+dx][ny+dy+next] == box && a[nx+dx][ny+dy+(2*next)] == opposite)
    {
        printf("CASE 2 REACHED\n");
        return 2;
    }
    // case 3: there is one box opposite of @
    if (isValid(nx+dx,ny+dy,a) && isValid(nx+dx,ny+dy+next,a) && a[nx+dx][ny+dy] == '.' && a[nx+dx][ny+dy+next] == box)
    {
        printf("CASE 3 REACHED\n");
        return 3;
    }
    // case 4: there is one box on the side of @
    if (isValid(nx+dx,ny+dy,a) && isValid(nx+dx,ny+dy+next,a) && a[nx+dx][ny+dy] == opposite && a[nx+dx][ny+dy+next] == '.')
    {
        printf("CASE 4 REACHED\n");
        return 4;
    }
    printf("IDFK EITHER\n");
    return 99; //WTF?

}
bool isThereSpaceToPushBoxesHorizontally(const int& x, const int& y, const vector<vector<char>>& a, char dir)
{
    auto [dx, dy] = getDir(dir);
    int nx = x+dx;
    int ny = y+dy;
    while (isValid(nx, ny, a))
    {
        if (a[nx][ny] == '.')
            return true;
        nx += dx;
        ny += dy;
    }
    return false;
}

bool isThereSpaceToPushBoxesVertically(const int& x, const int& y, const vector<vector<char>>& a, char dir)
{
    auto [dx, dy] = getDir(dir);
    int nx = x+dx;
    int ny = y+dy;

    int next = 0;
    char box = a[nx][ny];

    if (box == '[')
    {
        next++;
    }
    if (box == ']')
    {
        next--;
    }

    int what = boxTouchingTwoBoxes(x, y, a, dir);

    bool and0 = false;
    bool and1 = false;
    bool and2 = false;
    bool and3 = false;

    switch (what)
    {
        // There are no boxes...?
        case -1:
        {
            printf("PANIC!!!\n");
            return true;
        }
        // There are no boxes down
        case 0:
        {
            return true;
        }
        // There is one box down the middle
        case 1:
        {
            nx += dx;
            ny += dy;
            while (isValid(nx, ny, a))
            {
                if (a[nx][ny] == '.')
                    and0 = true;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            nx += dx;
            ny += dy;
            while (isValid(nx, ny + next, a))
            {
                if (a[nx][ny + next] == '.')
                    and1 = true;
                nx += dx;
                ny += dy;
            }
            if (and0 && and1)
            {
                return true;
            }
            return false;
        }
        // There are two boxes down the middle
        case 2:
        {
            nx += dx;
            ny += dy;
            while (isValid(nx, ny - next, a))
            {
                if (a[nx][ny - next] == '.')
                {
                    printf("condition 0: . found at %d, %d\n", nx,ny-next);
                    and0 = true;
                }
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            nx += dx;
            ny += dy;
            while (isValid(nx, ny, a))
            {
                if (a[nx][ny] == '.')
                {
                    printf("condition 1: . found at %d, %d\n", nx,ny);
                    and1 = true;
                }
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            nx += dx;
            ny += dy;
            while (isValid(nx, ny + next, a))
            {
                if (a[nx][ny + next] == '.')
                {
                    printf("condition 2: . found at %d, %d\n", nx,ny+next);
                    and2 = true;
                }
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            nx += dx;
            ny += dy;
            while (isValid(nx, ny + (2 * next), a))
            {
                if (a[nx][ny + (2 * next)] == '.')
                {
                    printf("condition 3: . found at %d, %d\n", nx,ny + (2*next));
                    and3 = true;
                }
                nx += dx;
                ny += dy;
            }
            if (and0 && and1 && and2 && and3)
            {
                printf("THERE IS SPACE!\n");
                return true;
            }
            return false;
        }
        // There is one box opposite of @
        case 3:
        {
            nx += dx;
            ny += dy;
            printf("%d, %d\n", nx, ny+next);
            while (isValid(nx, ny + next, a))
            {
                if (a[nx][ny + next] == '.')
                    and0 = true;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;


            nx += dx;
            ny += dy;
            printf("%d, %d\n", nx, ny+(2*next));
            while (isValid(nx, ny + (2 * next), a))
            {
                if (a[nx][ny + (2 * next)] == '.')
                    and1 = true;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            nx += dx;
            ny += dy;
            if (isValid(nx+dx, ny, a) && a[nx+dx][ny] == '.')
                and2 = true;

            if (and0 && and1 && and2)
            {
                return true;
            }
            return false;
        }
        // There is one box on the side of @
        case 4:
        {
            /*
            nx += dx;
            ny += dy;
            // Check all the coordinates of pushable boxes
            while (isValid(nx, ny, a))
            {
                
            }
            */
            nx += dx;
            ny += dy;
            while (isValid(nx, ny, a))
            {
                printf("condition 0: scanning %d, %d\n", nx, ny);
                if (a[nx][ny] == '.')
                {
                    printf("condition 0: %d, %d\n", nx, ny);
                    and0 = true;
                }
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            nx += dx;
            ny += dy;
            while (isValid(nx, ny - next, a))
            {
                printf("condition 1 scanning: %d, %d\n", nx, ny-next);
                if (a[nx][ny - next] == '.')
                {
                    printf("condition 1: %d, %d\n", nx, ny-next);
                    and1 = true;
                }
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            nx += dx;
            ny += dy;
            printf("condition 2: scanning %d, %d\n", nx, ny);
            if (isValid(nx+dx, ny+next, a) && a[nx+dx][ny+next] == '.')
            {
                printf("condition 2: %d, %d\n", nx, ny);
                and2 = true;
            }

            if (and0 && and1 && and2)
            {
                return true;
            }
            return false;
        }
        case 99:
        {
            printf("PANIC!!!\n");
            return false;
        }
    }
    return false;
}

void pushBoxesHorizontally(int& x, int& y, vector<vector<char>>& a, char dir) 
{
    auto [dx, dy] = getDir(dir);

    if (!isThereSpaceToPushBoxesHorizontally(x, y, a, dir)) 
    {
        return; 
    }

    int nx = x + dx;
    int ny = y + dy;
    
    a[x][y] = '.';

    int boxes = 0;

    char ya = a[nx][ny];
    while (a[nx][ny] != '.')
    {
        boxes++;
        nx += dx;
        ny += dy;
    }

    nx = x + dx;
    ny = y + dy;

    a[nx][ny] = '@';
    for (int i = 0; i < boxes; i++)
    {
        nx += dx;
        ny += dy;
        
        if (ya == '[')
        {
            if (i % 2 == 0)
            {
                a[nx][ny] = '[';
            }
            else
            {
                a[nx][ny] = ']';
            }
        }
        else if (ya == ']')
        {
            if (i % 2 == 0)
            {
                a[nx][ny] = ']';
            }
            else
            {
                a[nx][ny] = '[';
            }
        }
    }
    x += dx;
    y += dy;
}

void pushBoxesVertically(int& x, int& y, vector<vector<char>>& a, char dir)
{
    auto [dx, dy] = getDir(dir);
    int nx = x+dx;
    int ny = y+dy;

    int next = 0;
    char box = a[nx][ny];
    char opposite;
    int boxes;
    int boxes0 = 0;
    int boxes1 = 0;
    int boxes2 = 0;
    int boxes3 = 0;

    if (box == '[')
    {
        next++;
        opposite = ']';
    }
    if (box == ']')
    {
        next--;
        opposite = '[';
    }

    int what = boxTouchingTwoBoxes(x, y, a, dir);

    if (!isThereSpaceToPushBoxesVertically(x, y, a, dir))
    {
        return;
    }

    switch (what)
    {
        // There are no boxes
        case -1:
        {
            printf("PANIC!!!\n");
            return;
        }
        // There are no boxes down
        case 0:
        {
            a[nx+dx][ny+dy] = box;
            a[nx+dx][ny+dy+next] = opposite;
            a[nx][ny] = '@';
            a[nx][ny+next] = '.';
            a[x][y] = '.';
            x += dx;
            y += dy;
            return;
        }
        // There is one box down the middle
        case 1:
        {
            while (isValid(nx, ny, a) && a[nx][ny] == box)
            {
                boxes0++;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            while (isValid(nx, ny, a) && a[nx][ny+next] == opposite)
            {
                boxes1++;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;
            printf("%d, %d\n", boxes0, boxes1);

            boxes = boxes0 < boxes1 ? boxes0 : boxes1;
            printf("boxes: %d\n", boxes);

            for (int i = 0; i < boxes; i++)
            {
                a[nx+dx][ny+dy] = box;
                a[nx+dx][ny+dy+next] = opposite;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            a[nx][ny] = '@';
            a[nx][ny+next] = '.';
            a[x][y] = '.';
            x += dx;
            y += dy;
            return;
        }
        // There are two boxes down the middle
        case 2:
        {
            nx += dx;
            ny += dy;
            printf("%d, %d\n", nx, ny-next);
            while (isValid(nx, ny-next, a) && a[nx][ny-next] == box)
            {
                boxes0++;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            nx += dx;
            ny += dy;
            printf("%d, %d\n", nx, ny);
            while (isValid(nx, ny, a) && a[nx][ny] == opposite)
            {
                boxes1++;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            nx += dx;
            ny += dy;
            printf("%d, %d\n", nx, ny+next);
            while (isValid(nx, ny+next, a) && a[nx][ny+next] == box)
            {
                boxes2++;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            nx += dx;
            ny += dy;
            printf("%d, %d\n", nx, ny+(2*next));
            while (isValid(nx, ny+(2*next), a) && a[nx][ny+(2*next)] == opposite)
            {
                boxes3++;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            boxes = INT_MAX;
            if (boxes > boxes0)
                boxes = boxes0;
            if (boxes > boxes1)
                boxes = boxes1;
            if (boxes > boxes2)
                boxes = boxes2;
            if (boxes > boxes3)
                boxes = boxes3;
            printf("%d, %d, %d, %d\n", boxes0, boxes1, boxes2, boxes3);

            nx += dx;
            ny += dy;
            for (int i = 0; i < boxes; i++)
            {
                a[nx+dx][ny+dy-next] = box;
                a[nx+dx][ny+dy] = opposite;
                a[nx+dx][ny+dy+next] = box;
                a[nx+dx][ny+dy+(2*next)] = opposite;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            a[nx+dx][ny+dy-next] = '.';
            a[nx+dx][ny+dy+(2*next)] = '.';
            a[nx+dx][ny+dy] = box;
            a[nx+dx][ny+dy+next] = opposite;
            a[nx][ny] = '@';
            a[nx][ny+next] = '.';
            a[x][y] = '.';
            x += dx;
            y += dy;
            return;
        }
        // There is one box opposite of @
        case 3:
        {
            nx += dx;
            ny += dy;
            while (isValid(nx, ny+next, a) && a[nx][ny+next] == box)
            {
                boxes0++;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            nx += dx;
            ny += dy;
            while (isValid(nx, ny+(2*next), a) && a[nx][ny+(2*next)] == opposite)
            {
                boxes1++;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            boxes = boxes0 < boxes1 ? boxes0 : boxes1;

            nx += dx;
            ny += dy;
            for (int i = 0; i < boxes; i++)
            {
                a[nx+dx][ny+dy+next] = box;
                a[nx+dx][ny+dy+(2*next)] = opposite;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            a[nx+dx][ny+dy] = box;
            a[nx+dx][ny+dy+next] = opposite;
            a[nx+dx][ny+dy+(2*next)] = '.';
            a[nx][ny] = '@';
            a[nx][ny+next] = '.';
            a[x][y] = '.';
            x += dx;
            y += dy;
            return;
        }
        // There is one box on the side of @
        case 4:
        {
            while (isValid(nx, ny, a) && a[nx][ny] == opposite)
            {
                boxes0++;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            while (isValid(nx, ny-next, a) && a[nx][ny-next] == box)
            {
                boxes1++;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            boxes = boxes0 < boxes1 ? boxes0 : boxes1;

            nx += dx;
            ny += dy;
            for (int i = 0; i < boxes; i++)
            {
                a[nx+dx][ny+dy] = opposite;
                a[nx+dx][ny+dy-next] = box;
                nx += dx;
                ny += dy;
            }
            nx = x + dx;
            ny = y + dy;

            a[nx+dx][ny+dy-next] = '.';
            a[nx+dx][ny+dy] = box;
            a[nx+dx][ny+dy+next] = opposite;
            a[nx][ny] = '@';
            a[nx][ny+next] = '.';
            a[x][y] = '.';
            x += dx;
            y += dy;
            return;
        }
        case 99:
        {
            printf("PANIC!!!\n");
            return;
        }
    }
}

void robot(vector<vector<char>>& a, const vector<char>& moves) 
{
    int x, y; 

    for (int i = 0; i < a.size(); i++) 
    {
        for (int j = 0; j < a[0].size(); j++) 
        {
            if (a[i][j] == '@') {
                x = i;
                y = j;
                break;
            }
        }
    }

    for (char move : moves) {
        auto [dx, dy] = getDir(move);
        int nx = x + dx; 
        int ny = y + dy;

        printf("MOVE: %c\n", move);
        for (int i = 0; i < a.size(); i++)
        {
            for (int j = 0; j < a[0].size(); j++)
            {
                printf("%c ", a[i][j]);
            }
            printf("\n");
        }
        if (isValid(nx, ny, a)) 
        {
            if (a[nx][ny] == '.') 
            { 
                a[nx][ny] = '@'; 
                a[x][y] = '.';  

                x = nx;
                y = ny;
            } 
            else if (a[nx][ny] == '[' || a[nx][ny] == ']') 
            { 
                if (move == '<' || move == '>')
                {
                    if(isThereSpaceToPushBoxesHorizontally(x, y, a, move))
                    {
                        pushBoxesHorizontally(x, y, a, move);
                    }
                }
                if (move == '^' || move == 'v')
                {
                    if(isThereSpaceToPushBoxesVertically(x, y, a, move))
                    {
                        pushBoxesVertically(x, y, a, move);
                    }
                }
            }
        }
    }
}

int distance(int x, int y)
{
    return(100 * x + y);
}

ULL gps(vector<vector<char>>& a)
{
    ULL sum = 0;
    vector<pair<int, int>> boxes;
    
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            if (a[i][j] == '[')
            {
                boxes.push_back(make_pair(i,j));
            }
        }
    }

    for (const auto& box : boxes)
    {
        sum += distance(box.first, box.second);
    }
    return sum;
}

int main(int argc, char *argv[]) 
{
    ifstream input_file(argv[1]);
    vector<vector<char>> a;
    vector<char> moves;

    if (!input_file) 
    {
        cerr << "error opening file" << endl;
        return 1;
    }

    string line;

    while (getline(input_file, line)) 
    {
        if (line.empty())
        {
            break;
        }
        vector<char> row(line.begin(), line.end());
        a.push_back(row);
    }

    while (getline(input_file, line)) 
    {
        for (char c : line)
        {
            moves.push_back(c);
        }
    }
    input_file.close();

    convertMap(a);
    robot(a, moves);

    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            printf("%c ", a[i][j]);
        }
        printf("\n");
    }
    printf("sum: %llu\n", gps(a)); 
}

