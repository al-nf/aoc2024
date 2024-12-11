#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <utility>
using namespace std;

unsigned long long stones(vector<unsigned long long>& data, int reps)
{
    unsigned long long zeroes = 0;
    unsigned long long ones = 0;

    auto removeZerosAndOnes = [&zeroes, &ones](vector<unsigned long long>& data) 
    {
        auto it = data.begin();
        while (it != data.end()) 
        {
            if (*it == 0) 
            {
                zeroes++;
                it = data.erase(it); 
            } 
            else if (*it == 1) 
            {
                ones++;
                it = data.erase(it); 
            } 
            else 
            {
                ++it;
            }
        }
    };

    removeZerosAndOnes(data);

    auto evenDigits = [](unsigned long long num)
    {
        int count = 0;
        while (num != 0)
        {
            num /= 10;
            count++;
        }
        return count % 2 == 0;
    };

    auto split = [](unsigned long long num) -> pair<unsigned long long, unsigned long long>
    {
        if (num == 0)
        {
            return {0, 0};
        }

        int digits = static_cast<int>(log10(num)) + 1;
        unsigned long long div = 1;
        for (int i = 0; i < digits / 2; i++)
        {
            div *= 10;
        }

        unsigned long long part1 = num / div;
        unsigned long long part2 = num % div;

        return {part1, part2};
    };

    auto blink = [&data, &evenDigits, &split, &zeroes, &ones]() 
    {
        vector<unsigned long long> tmp;
        unsigned long long newZeroes = 0;
        unsigned long long newOnes = ones; 
        for (size_t i = 0; i < data.size(); i++) 
        {
            if (evenDigits(data[i])) 
            {
                pair<unsigned long long, unsigned long long> splitNum = split(data[i]);
                if (splitNum.first == 0)
                    newZeroes++;
                else if (splitNum.first == 1)
                    newOnes++;
                else
                    tmp.push_back(splitNum.first);
                if (splitNum.second == 0)
                    newZeroes++;
                else if (splitNum.second == 1)
                    newOnes++;
                else
                    tmp.push_back(splitNum.second); 
            } 
            else 
            {
                tmp.push_back(data[i] * 2024);
            }
        }
        for (unsigned long long i = 0; i < ones; i++)
        {
            tmp.push_back(2024);
        }
        data = move(tmp);
        zeroes = newZeroes;
        ones = newOnes;
    };

    for (int i = 0; i < reps; i++)
    {
        /*
        for (unsigned long long num : data)
        {
            cout << num << " ";
        }
        cout << endl;
        */
        blink();
    }
    return data.size() + zeroes + ones;
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
        
        while (ss >> value)
        {
            data.push_back(value); 
        }
    }

    printf("stones: %llu\n", stones(data, 25));
}

