#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

unordered_map<unsigned long long, vector<unsigned long long>> memo;

vector<unsigned long long> transform(unsigned long long num) 
{
    if (memo.find(num) != memo.end()) 
    {
        return memo[num];
    }

    vector<unsigned long long> result;

    if (num == 0) 
    {
        result.push_back(1); 
    }
    else 
    {
        string num_str = to_string(num);
        if (num_str.size() % 2 == 0) 
        {
            size_t mid = num_str.size() / 2;
            unsigned long long left = stoull(num_str.substr(0, mid));
            unsigned long long right = stoull(num_str.substr(mid));
            result.push_back(left);
            result.push_back(right);
        } 
        else 
        {
            result.push_back(num * 2024); 
        }
    }

    memo[num] = result;

    return result;
}

unsigned long long countStones(vector<unsigned long long>& stones, int blinks) 
{
    if (blinks == 0) 
    {
        return stones.size();
    }

    vector<unsigned long long> next_stones;
    for (unsigned long long stone : stones) 
    {
        vector<unsigned long long> transformed = transform(stone);
        next_stones.insert(next_stones.end(), transformed.begin(), transformed.end());
    }

    return countStones(next_stones, blinks - 1);
}

int main(int argc, char *argv[]) 
{
    ifstream input_file(argv[1]);
    vector<unsigned long long> data;

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

    printf("stones: %llu\n", countStones(data, 75));
}

