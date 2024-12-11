#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <utility>
#include <omp.h>
using namespace std;

int stones(vector<unsigned long long>& data, int reps)
{
    
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
    auto blink = [&data, &evenDigits, &split]() 
    {
        vector<unsigned long long> tmp;
        tmp.reserve(data.size() * 2);

        #pragma omp parallel
        {
            vector<unsigned long long> localTmp;
            localTmp.reserve(data.size() * 2);

            #pragma omp for
            for (size_t i = 0; i < data.size(); i++) 
            {
                if (data[i] == 0) 
                {
                    localTmp.push_back(1);
                } 
                else if (evenDigits(data[i])) 
                {
                    pair<unsigned long long, unsigned long long> splitNum = split(data[i]);
                    localTmp.push_back(splitNum.first);
                    localTmp.push_back(splitNum.second);
                } 
                else 
                {
                    localTmp.push_back(data[i] * 2024); 
                }
            }
            #pragma omp critical
            {
                tmp.insert(tmp.end(), localTmp.begin(), localTmp.end());
            }
        }
        data = move(tmp);
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
    return data.size();

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

    printf("stones: %d\n", stones(data, 75));
}

