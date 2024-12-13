#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>
#include <climits>

using namespace std;

int extendedGCD(int a, int b, int& x, int& y) 
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}


vector<tuple<int, int, int>> dioph(int ax, int bx, int c) 
{
    vector<tuple<int, int, int>> solutions;
    int x0, y0;
    int g = extendedGCD(ax, bx, x0, y0);
    
    if (c % g != 0) {
        return solutions;
    }

    x0 *= c / g;
    y0 *= c / g;

    int stepX = bx / g;
    int stepY = ax / g;

    int tMinX = ceil((0 - x0) / (double)stepX);
    int tMaxX = floor((100 - x0) / (double)stepX);

    int tMinY = ceil((y0 - 100) / (double)stepY);
    int tMaxY = floor((y0 - 0) / (double)stepY);

    int tMin = max(tMinX, tMinY);
    int tMax = min(tMaxX, tMaxY);

    for (int t = tMin; t <= tMax; t++) 
    {
        int x = x0 + t * stepX;
        int y = y0 - t * stepY;
        solutions.push_back(make_tuple(x, y, c));
        //printf("Solution found: x = %d, y = %d\n", x, y);
    }

    return solutions;
}

int main(int argc, char *argv[]) 
{
    ifstream input_file(argv[1]);
    vector<pair<int, int>> buttonA;
    vector<pair<int, int>> buttonB;
    vector<pair<int, int>> prize;
    unsigned long long sum = 0;

    if (!input_file) 
    {
        cerr << "error opening file" << endl;
        return 1;
    }

    string line;
    int idx = 0;

    regex buttonPattern(R"(X[=+](\d+), Y[=+](\d+))");
    regex prizePattern(R"(X=(\d+), Y=(\d+))");

    while (getline(input_file, line)) 
    {
        switch (idx % 4) 
        {
            case 0: { 
                smatch match;
                if (regex_search(line, match, buttonPattern) && match.size() == 3) 
                {
                    int x = stoi(match[1].str());
                    int y = stoi(match[2].str());
                    buttonA.push_back({x, y});
                }
                break;
            }
            case 1: { 
                smatch match;
                if (regex_search(line, match, buttonPattern) && match.size() == 3) 
                {
                    int x = stoi(match[1].str());
                    int y = stoi(match[2].str());
                    buttonB.push_back({x, y});
                }
                break;
            }
            case 2: {
                smatch match;
                if (regex_search(line, match, prizePattern) && match.size() == 3) 
                {
                    int x = stoi(match[1].str());
                    int y = stoi(match[2].str());
                    prize.push_back({x, y});
                }
                break;
            }
            case 3: {
                break;
            }
        }
        idx++;
    }


    int minCost, cost;
    vector<tuple<int, int, int>> solutionsX;
    vector<tuple<int, int, int>> solutionsY;


    for (int i = 0; i < buttonA.size(); i++)
    {
        solutionsX = dioph(buttonA[i].first, buttonB[i].first, prize[i].first);
        solutionsY = dioph(buttonA[i].second, buttonB[i].second, prize[i].second);

        minCost = INT_MAX;

        if (solutionsX.size() != 0 && solutionsY.size() != 0)
        {
            for (tuple <int, int, int> solution : solutionsX)
            {
                if ((buttonA[i].second) * get<0>(solution) + (buttonB[i].second) * get<1>(solution) == prize[i].second)
                {
                    cost = 3 * get<0>(solution) + get<1>(solution);
                    if (cost < minCost)
                    {
                            //printf("minCost set to %d * %d + %d * %d = %d, %d * %d + %d * %d = %d\n", buttonA[i].first, get<0>(solution), buttonB[i].first, get<1>(solution), prize[i].first, buttonA[i].second, get<0>(solution), buttonB[i].second, get<1>(solution), prize[i].second);
                            //printf("Actual answers: %d, %d\n", buttonA[i].first * get<0>(solution) + buttonB[i].first * get<1>(solution), buttonA[i].second * get<0>(solution) + buttonB[i].second * get<1>(solution));
                        minCost = cost;
                    }
                }
                else
                {
                    //printf("Solution x = %d, y = %d is invalid\n", get<0>(solution), get<1>(solution));
                }
            }

            for (tuple <int, int, int> solution : solutionsY)
            {
                if ((buttonA[i].first) * get<0>(solution) + (buttonB[i].first) * get<1>(solution) == prize[i].first)
                {
                    cost = 3 * get<0>(solution) + get<1>(solution);
                    if (cost < minCost)
                    {
                        //printf("minCost set to %d * %d + %d * %d = %d, %d * %d + %d * %d = %d\n", buttonA[i].first, get<0>(solution), buttonB[i].first, get<1>(solution), prize[i].first, buttonA[i].second, get<0>(solution), buttonB[i].second, get<1>(solution), prize[i].second);
                        //printf("Actual answers: %d, %d\n", buttonA[i].first * get<0>(solution) + buttonB[i].first * get<1>(solution), buttonA[i].second * get<0>(solution) + buttonB[i].second * get<1>(solution));
                        minCost = cost;
                    }
                }
                else
                {
                    //printf("Solution x = %d, y = %d is invalid\n", get<0>(solution), get<1>(solution));
                }
            }
        }
        if (minCost != INT_MAX)
        {
            sum += minCost;
            //printf("added cost %d\n", minCost);
        }
    }

    input_file.close();

    printf("sum: %llu\n", sum);
}

