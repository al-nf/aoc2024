#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

unordered_map<unsigned long long, unordered_map<int, unsigned long long>> dict;

unsigned long long stones(unsigned long long stone, int reps)
{    

    auto split = [](unsigned long long num) -> pair<unsigned long long, unsigned long long>
    {
        if (num == 0)
        {
            return {0, 0};
        }

        int digits = static_cast<unsigned long long>(log10(num)) + 1;
        unsigned long long div = 1;
        for (int i = 0; i < digits / 2; i++)
        {
            div *= 10;
        }

        unsigned long long part1 = num / div;
        unsigned long long part2 = num % div;

        return {part1, part2};
    };

    if (reps == 0)
    {
        dict[stone][0] = 1;
        return 1;
    }

    if (dict.find(stone) != dict.end())
    {
        if (dict[stone].find(reps) != dict[stone].end())
        {
            return dict[stone][reps];
        }
    }

    if ((static_cast<unsigned long long>(log10(stone) + 1)) % 2 == 0)
    {
        pair<unsigned long long, unsigned long long> splitNum = split(stone);
        dict[stone][reps] = stones(splitNum.first, reps - 1) + stones(splitNum.second, reps - 1);
    }
    else
    {
        dict[stone][reps] = stones(stone * 2024, reps - 1);
    }
    return dict[stone][reps];
}

int main(int argc, char *argv[]) 
{
    ifstream input_file(argv[1]);
    vector<unsigned long long> data;
    unsigned long long sum = 0;

    if (!input_file) 
    {
        cerr << "error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(input_file, line)) 
    {
        stringstream ss(line);
        unsigned long long value;

        while (ss >> value) {
            data.push_back(value);
        }
    }

    for (unsigned long long num : data)
    {
        sum += stones(num, 6);
    }
    printf("stones: %llu\n", sum);
}

