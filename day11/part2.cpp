#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

unordered_map<unsigned long long, unordered_map<int, unsigned long long>> memo;

pair<unsigned long long, unsigned long long> split(unsigned long long num) 
{
    if (num == 0) return {0, 0};
    int digits = static_cast<int>(log10(num)) + 1;
    unsigned long long div = 1;
    for (int i = 0; i < digits / 2; i++) 
    {
        div *= 10;
    }
    unsigned long long part1 = num / div;
    unsigned long long part2 = num % div;
    return {part1, part2};
}

unsigned long long stones(unsigned long long stone, int reps) 
{
    if (reps == 0) return 1;

    if (memo[stone].count(reps)) 
        return memo[stone][reps];

    unsigned long long term = 0;

    if (stone == 0) 
    {
        term = stones(1, reps - 1);
    } 
    else if ((static_cast<int>(log10(stone)) + 1) % 2 == 0) 
    {
        auto [part1, part2] = split(stone);
        term = stones(part1, reps - 1) + stones(part2, reps - 1);
    } 
    else 
    {
        term = stones(stone * 2024, reps - 1);
    }

    memo[stone][reps] = term;
    return term;
}

int main(int argc, char *argv[]) 
{
    ifstream inputFile(argv[1]);
    vector<unsigned long long> data;
    unsigned long long sum = 0;

    if (!inputFile) 
    {
        cerr << "error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) 
    {
        stringstream ss(line);
        unsigned long long value;

        while (ss >> value) {
            data.push_back(value);
        }
    }

    for (unsigned long long num : data)
    {
        sum += stones(num, 75);
    }
    printf("stones: %llu\n", sum);
}

