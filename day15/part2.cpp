#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

void convertMap(vector<vector<char>>& warehouse)
{
    vector<vector<char>> newMap;

    for (int i = 0; i < warehouse.size(); i++)
    {
        vector<char> row;
        for (int j = 0; j < warehouse[0].size(); j++)
        {
            switch (warehouse[i][j])
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
    warehouse.assign(newMap.begin(), newMap.end());
}

bool inBounds(int x, int y, const vector<vector<char>>& warehouse)
{
    return (x >= 0 && x < warehouse.size() && y >= 0 && y < warehouse[0].size());
}
bool isValid(int x, int y, const vector<vector<char>>& warehouse)
{
    if (inBounds(x, y, warehouse))
    {
        if (warehouse[x][y] != '#')
        {
            return true;
        }
    }
    return false;

}

bool boxTouchingTwoBoxes(int& x, int& y, const vector<vector<char>>& warehouse, char dir)
{
    if (dir == '<' || dir == '>')
    {
        return false;
    }
    else if (dir == '^')
    {
        if (!inBounds(x-2, y, warehouse))
        {
            return false;
        }
        if ((warehouse[x-1][y] == '[' && warehouse[x-2][y] == ']') || ((warehouse[x-1][y] == ']' && warehouse[x-2][y] == '[')))
        {
            printf("false positive here1!\n");
            return true;
        }
        return false;
    }
    else if (dir == 'v')
    {
        if (!inBounds(x+2, y, warehouse))
        {
            return false;
        }
        if ((warehouse[x+1][y] == '[' && warehouse[x+2][y] == ']') || ((warehouse[x+1][y] == ']' && warehouse[x+2][y] == '[')))
        {
            printf("false positive here2!\n");
            return true;
        }
        return false;
    }

}
bool isThereSpaceToPushBoxesHorizontally(int& x, int& y, const vector<vector<char>>& warehouse, char dir)
{
    auto [dx, dy] = getDir(dir);
    int nx = x;
    int ny = y;

    while (isValid(nx, ny, warehouse))
    {
        if (warehouse[nx][ny] == '.')
            return true;
        nx += dx;
        ny += dy;
    }
    return false;
}

bool isThereSpaceToPushBoxesVertically(int& x, int& y, const vector<vector<char>>& warehouse, char dir)
{
    auto [dx, dy] = getDir(dir);
    int nx = x+dx;
    int ny = y+dy;

    printf("\nNX: %d, NY: %d\n", nx, ny);

    char ya = warehouse[nx][ny];

    if (!boxTouchingTwoBoxes(x, y, warehouse, dir))
    {
        printf("aligned case isSpace\n");
        if (ya == '[')
        {
            if (dir == '^')
            {
                while (isValid(nx, ny, warehouse) && isValid(nx, ny+1, warehouse))
                {
                    if (warehouse[nx][ny] == '.' && warehouse[nx][ny+1] == '.')
                    {
                        return true;
                    }
                    nx--;
                }
                printf("eee\n");
                return false;
            }
            else
            {
                while (isValid(nx, ny, warehouse) && isValid(nx, ny+1, warehouse))
                {
                    if (warehouse[nx][ny] == '.' && warehouse[nx][ny+1] == '.')
                    {
                        return true;
                    }
                    nx++;
                }
                printf("fff\n");
                return false;
            }
        }
        else
        {
            printf("testing space at (%d, %d) and (%d, %d)!\n", nx, ny, nx, ny-1);
            if (dir == '^')
            {
                while (isValid(nx, ny, warehouse) && isValid(nx, ny-1, warehouse))
                {
                    if (warehouse[nx][ny] == '.' && warehouse[nx][ny-1] == '.')
                    {
                        printf("There is space at (%d, %d) and (%d, %d)!\n", nx, ny, nx, ny-1);
                        return true;
                    }
                    nx--;
                }
                printf("ggg\n");
                return false;
            }
            else
            {
                while (isValid(nx, ny, warehouse) && isValid(nx, ny-1, warehouse))
                {
                    if (warehouse[nx][ny] == '.' && warehouse[nx][ny-1] == '.')
                    {
                        return true;
                    }
                    nx++;
                }
                printf("hhh\n");
                return false;
            }
        }
        return false;
    }
    else
    {
        nx += 2 *dx;
        ny += 2 * dy;
        printf("2box case isSpace\n");
        if (ya == '[')
        {
            if (isValid(x + 2 * dx, y + 2 * dy, warehouse) && isValid(x + 2 * dx, y + 2 * dy+1, warehouse) && warehouse[x + 2 * dx][y + 2 * dy] == '.' && warehouse[x + 2 * dx][y + 2 * dy+1] == '.')
            {
                return true;
            }
            if (dir == '^')
            {
                while (isValid(nx, ny-1, warehouse) && isValid(nx, ny, warehouse) && isValid(nx, ny+1, warehouse) && isValid(nx, ny+2, warehouse))
                {
                    if (warehouse[nx][ny-1] == '.' && warehouse[nx][ny] == '.' && warehouse[nx][ny+1] == '.' && warehouse[nx][ny+2] == '.')
                    {
                        printf("%c, %c, %c, %c\n", warehouse[nx][ny-1], warehouse[nx][ny] ,warehouse[nx][ny+1] ,warehouse[nx][ny+2] );
                        printf("(%d, %d), (%d, %d),(%d, %d),(%d, %d)\n", nx, ny-1, nx, ny, nx,ny+1,nx,ny+2);
                        printf("There is space!\n");
                        return true;
                    }
                    nx--;
                }
                printf("eee\n");
                return false;
            }
            else
            {
                while (isValid(nx, ny-1, warehouse) && isValid(nx, ny, warehouse) && isValid(nx, ny+1, warehouse) && isValid(nx, ny+2, warehouse))
                {
                    if (warehouse[nx-1][ny] == '.' && warehouse[nx][ny] == '.' && warehouse[nx+1][ny] == '.' && warehouse[nx+2][ny] == '.')
                    {
                        printf("%c, %c, %c, %c\n", warehouse[nx][ny-1], warehouse[nx][ny] ,warehouse[nx][ny+1] ,warehouse[nx][ny+2] );
                        printf("(%d, %d), (%d, %d),(%d, %d),(%d, %d)\n", nx, ny-1, nx, ny, nx,ny+1,nx,ny+2);
                        printf("There is space!\n");
                        return true;
                    }
                    nx++;
                }
                printf("fff\n");
                return false;
            }
        }
        else
        {
            if (isValid(x + 2 * dx, y + 2 * dy, warehouse) && isValid(x + 2 * dx, y + 2 * dy-1, warehouse) && warehouse[x + 2 * dx][y + 2 * dy] == '.' && warehouse[x + 2 * dx][y + 2 * dy-1] == '.')
            {
                return true;
            }
            if (dir == 'v')
            {
                while (isValid(nx, ny-2, warehouse) && isValid(nx, ny-1, warehouse) && isValid(nx, ny, warehouse) && isValid(nx, ny+1, warehouse))
                {
                    if (warehouse[nx-1][ny] == '.' && warehouse[nx][ny] == '.' && warehouse[nx+1][ny] == '.' && warehouse[nx+2][ny] == '.')
                    {
                        printf("%c, %c, %c, %c\n", warehouse[nx][ny-2], warehouse[nx][ny-1] ,warehouse[nx][ny] ,warehouse[nx][ny+1] );
                        printf("(%d, %d), (%d, %d),(%d, %d),(%d, %d)\n", nx, ny-2, nx, ny-1, nx,ny,nx,ny+1);
                        printf("There is space!\n");
                        return true;
                    }
                    nx--;
                }
                printf("ggg\n");
                return false;
            }
            else
            {
                while (isValid(nx, ny-2, warehouse) && isValid(nx, ny-1, warehouse) && isValid(nx, ny, warehouse) && isValid(nx, ny+1, warehouse))
                {
                    if (warehouse[nx-1][ny] == '.' && warehouse[nx][ny] == '.' && warehouse[nx+1][ny] == '.' && warehouse[nx+2][ny] == '.')
                    {
                        printf("%c, %c, %c, %c\n", warehouse[nx][ny-2], warehouse[nx][ny-1] ,warehouse[nx][ny] ,warehouse[nx][ny+1] );
                        printf("(%d, %d), (%d, %d),(%d, %d),(%d, %d)\n", nx, ny-2, nx, ny-1, nx,ny,nx,ny+1);
                        printf("There is space!\n");
                        return true;
                    }
                    nx++;
                }
                printf("hhh\n");
                return false;
            }
        }
        return false;
    }
}
void pushBoxesHorizontally(int& x, int& y, vector<vector<char>>& warehouse, char dir) 
{
    auto [dx, dy] = getDir(dir);

    if (!isThereSpaceToPushBoxesHorizontally(x, y, warehouse, dir)) 
    {
        return; 
    }

    int nx = x + dx;
    int ny = y + dy;
    
    warehouse[x][y] = '.';
    x = nx;
    y = ny;

    int boxes = 0;

    char ya = warehouse[nx][ny];
    while (warehouse[nx][ny] != '.')
    {
        boxes++;
        nx += dx;
        ny += dy;
    }

    nx = x;
    ny = y;
    warehouse[x][y] = '@';
    for (int i = 0; i < boxes; i++)
    {
        nx += dx;
        ny += dy;
        
        if (ya == '[')
        {
            if (i % 2 == 0)
            {
                warehouse[nx][ny] = '[';
            }
            else
            {
                warehouse[nx][ny] = ']';
            }
        }
        else if (ya == ']')
        {
            if (i % 2 == 0)
            {
                warehouse[nx][ny] = ']';
            }
            else
            {
                warehouse[nx][ny] = '[';
            }
        }
    }
}
void pushBoxesVertically(int& x, int& y, vector<vector<char>>& warehouse, char dir) 
{
    auto [dx, dy] = getDir(dir);

    if (!isThereSpaceToPushBoxesVertically(x, y, warehouse, dir)) 
    {
        printf("no space!\n");
        return; 
    }

    printf("dx: %d, dy: %d\n", dx, dy);
    int nx = x + dx;
    int ny = y + dy;
    
    warehouse[x][y] = '.';
    x = nx;
    y = ny;

    int boxes = 0;

    char ya = warehouse[nx][ny];
    while (isValid(nx, ny, warehouse) && warehouse[nx][ny] != '.')
    {
        boxes++;
        nx += dx;
        ny += dy;
    }
    printf("boxes: %d\n", boxes);

    nx = x + dx;
    ny = y + dy;

    if (boxTouchingTwoBoxes(x, y, warehouse, dir))
    {
        printf("two boxes touching case\n");
        if (ya == '[')
        {
            if (isValid(x,y,warehouse) && isValid(x,y+1,warehouse) && isValid(nx,ny-1,warehouse) && isValid(nx,ny,warehouse) && isValid(nx,ny+1,warehouse) && isValid(nx,ny+2,warehouse))
            {
                warehouse[x][y] = '@';
                warehouse[x][y+1] = '.';
                warehouse[nx][ny-1] = '.';
                warehouse[nx][ny] = '[';
                warehouse[nx][ny+1] = ']';
                warehouse[nx][ny+2] = '.';
                for (int i = 2; i <= boxes; i++)
                {
                    if (isValid(nx+i*dx,ny-1,warehouse) && isValid(nx+i*dx,ny,warehouse) && isValid(nx+i*dx,ny+1,warehouse) && isValid(nx+i*dx,ny+2,warehouse))
                    {
                        warehouse[nx + i * dx][ny-1] = '[';
                        warehouse[nx + i * dx][ny] = ']';
                        warehouse[nx + i * dx][ny+1] = '[';
                        warehouse[nx + i * dx][ny+2] = ']';
                    }
                }
            }
        }
        else
        {
            if (isValid(x,y,warehouse) && isValid(x,y-1,warehouse) && isValid(nx,ny-2,warehouse) && isValid(nx,ny-1,warehouse) && isValid(nx,ny,warehouse) && isValid(nx,ny+1,warehouse))
            {
                warehouse[x][y] = '@';
                warehouse[x][y-1] = '.';
                warehouse[nx][ny-2] = '.';
                warehouse[nx][ny] = ']';
                warehouse[nx][ny-1] = '[';
                warehouse[nx][ny+1] = '.';
                for (int i = 1; i < boxes; i++)
                {
                    if (isValid(nx+i*dx,ny-2,warehouse) && isValid(nx+i*dx,ny-1,warehouse) && isValid(nx+i*dx,ny,warehouse) && isValid(nx+i*dx,ny+1,warehouse))
                    {
                        warehouse[nx + i * dx][ny-2] = '[';
                        warehouse[nx + i * dx][ny-1] = ']';
                        warehouse[nx + i * dx][ny] = '[';
                        warehouse[nx + i * dx][ny+1] = ']';
                    }
                }
            }
        }
    }
    else
    {
        printf("aligned case\n");
        if (ya == '[')
        {
            warehouse[nx][ny] = '@';
            warehouse[nx][ny+1] = '.';
            for (int i = 1; i <= boxes; i++)
            {
                if (isValid(nx+i*dx, ny, warehouse) && isValid(nx+i*dx, ny+1, warehouse))
                    warehouse[nx + i * dx][ny] = '[';
                    warehouse[nx + i * dx][ny+1] = ']';
                    warehouse[nx-dx][ny-dy] = '.';
                    warehouse[nx-dx][ny-dy+1] = '.';
            }
        }
        else
        {
            warehouse[nx][ny] = '@';
            warehouse[nx][ny-1] = '.';
            for (int i = 1; i <= boxes; i++)
            {
                if (isValid(nx+i*dx, ny, warehouse))
                    warehouse[nx + i * dx][ny] = '[';
                if (isValid(nx+i*dx, ny-1, warehouse))
                    warehouse[nx + i * dx][ny-1] = ']';
            }
        }
    }
}

void robot(vector<vector<char>>& warehouse, const vector<char>& moves) 
{
    int x, y; 

    for (int i = 0; i < warehouse.size(); i++) 
    {
        for (int j = 0; j < warehouse[0].size(); j++) 
        {
            if (warehouse[i][j] == '@') {
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
        
        printf("BEFORE: \n");
        for (int i = 0; i < warehouse.size(); i++)
        {
            for (int j = 0; j < warehouse[0].size(); j++)
            {
                printf("%c ", warehouse[i][j]);
            }
            printf("\n");
        }

        if (isValid(nx, ny, warehouse)) 
        {
            printf("COMMENCING MOVEMENT IN %c DIRECTION\n", move);
            if (warehouse[nx][ny] == '.') 
            { 
                warehouse[nx][ny] = '@'; 
                warehouse[x][y] = '.';  

                x = nx;
                y = ny;
            } 
            else if (warehouse[nx][ny] == '[' || warehouse[nx][ny] == ']') 
            { 
                if (move == '<' || move == '>')
                {
                    if(isThereSpaceToPushBoxesHorizontally(x, y, warehouse, move))
                    {
                        printf("Pushing blocks horizontally\n");
                        pushBoxesHorizontally(x, y, warehouse, move);
                    }
                }
                else
                {
                    if(isThereSpaceToPushBoxesVertically(x, y, warehouse, move))
                    {
                        printf("Pushing blocks vertically\n");
                        pushBoxesVertically(x, y, warehouse, move);
                    }
                }
            }
        }
        printf("\nAFTER: \n");
        for (int i = 0; i < warehouse.size(); i++)
        {
            for (int j = 0; j < warehouse[0].size(); j++)
            {
                printf("%c ", warehouse[i][j]);
            }
            printf("\n");
        }
        printf("current pos: %d, %d\n", x, y);
    }
}

int distance(int x, int y)
{
    return(100 * x + y);
}

ULL gps(vector<vector<char>>& warehouse)
{
    ULL sum = 0;
    vector<pair<int, int>> boxes;
    
    for (int i = 0; i < warehouse.size(); i++)
    {
        for (int j = 0; j < warehouse[0].size(); j++)
        {
            if (warehouse[i][j] == '[')
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
    vector<vector<char>> warehouse;
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
        warehouse.push_back(row);
    }

    while (getline(input_file, line)) 
    {
        for (char c : line)
        {
            moves.push_back(c);
        }
    }
    input_file.close();

    convertMap(warehouse);
    robot(warehouse, moves);

    printf("sum: %llu\n", gps(warehouse)); 
}

