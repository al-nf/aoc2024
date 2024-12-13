#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <regex>
#include <cmath>
#include <climits>
#include <numeric>
#include <algorithm>

#define LL long long

using namespace std;

pair<LL, LL> cramer(LL a1, LL b1, LL a2, LL b2, LL c1, LL c2)
{
    return make_pair
    (
        (c1*b2 - c2*b1)/(a1*b2 - a2*b1),
        (a1*c2 - a2*c1)/(a1*b2 - a2*b1)
    );
}

int main(int argc, char *argv[]) 
{
    ifstream input_file(argv[1]);
    vector<pair<LL, LL>> buttonA;
    vector<pair<LL, LL>> buttonB;
    vector<pair<LL, LL>> prize;
    LL sum = 0;

    if (!input_file) 
    {
        cerr << "error opening file" << endl;
        return 1;
    }

    string line;
    LL idx = 0;

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
                    LL x = stoll(match[1].str());
                    LL y = stoll(match[2].str());
                    buttonA.push_back({x, y});
                }
                break;
            }
            case 1: { 
                smatch match;
                if (regex_search(line, match, buttonPattern) && match.size() == 3) 
                {
                    LL x = stoll(match[1].str());
                    LL y = stoll(match[2].str());
                    buttonB.push_back({x, y});
                }
                break;
            }
            case 2: {
                smatch match;
                if (regex_search(line, match, prizePattern) && match.size() == 3) 
                {
                    LL x = stoll(match[1].str())+10000000000000;
                    //LL x = stoll(match[1].str());
                    LL y = stoll(match[2].str())+10000000000000;
                    //LL y = stoll(match[2].str());
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


    for (LL i = 0; i < buttonA.size(); i++)
    {
        pair<LL, LL> buttons = cramer(buttonA[i].first, buttonB[i].first, buttonA[i].second, buttonB[i].second, prize[i].first, prize[i].second);
        if ((buttonA[i].first * buttons.first + buttonB[i].first * buttons.second == prize[i].first) && (buttonA[i].second * buttons.first + buttonB[i].second * buttons.second == prize[i].second))
        {
            sum += (3 * buttons.first + buttons.second);
            //printf("valid: %lld, %lld\n", buttons.first, buttons.second);
        }
        else 
        {
            //printf("invalid: %lld, %lld\n", buttons.first, buttons.second);
        }
    }

    input_file.close();

    printf("sum: %lld\n", sum);
}

