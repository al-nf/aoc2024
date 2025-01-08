#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

#define ULL unsigned long long

using namespace std;

int calc(const int& n)
{
    int k = n;
    k = ((k << 6) ^ k) & 0xFFFFFF;
    k = ((k >> 5) ^ k) & 0xFFFFFF;
    k = ((k << 11) ^ k) & 0xFFFFFF;
    return k;
}

int seqConverter(int* seq)
{
    int k = 0;
    for (int i = 0; i < 4; i++)
    {
        k *= 19;
        k += seq[i] + 9;
    }
    return k;
}

void solve(const vector<int>& nums)
{
    int sequences[(long unsigned int)pow(19, 4)] = {0};
    int visited[(long unsigned int)pow(19, 4)] = {0};

    int buyer = 1;
    int prices[2000];
    int changes[2000];

    for (int num : nums)
    {
        int res = num;
        int prev = 0;
        for (int i = 0; i < 2000; i++)
        {
            res = calc(res);
            prices[i] = (res % 10);
            changes[i] = ((res % 10) - prev);
            prev = res % 10;
        }
        for (int i = 1; i+3 < 2000; i++)
        {
            int seq = seqConverter(&changes[i]);
            if (visited[seq] != buyer)
            {
                visited[seq] = buyer;
                sequences[seq] += prices[i+3];
            }
        }
        buyer++;
    }

    int bana = 0;

    for (int i = 0; i < pow(19, 4); i++)
    {
        if (sequences[i] > bana)
        {
            bana = sequences[i];
        }
    }

    printf("bananas: %d\n", bana);

}
int main(int argc, char* argv[])
{
    ifstream inputFile(argv[1]);

    vector<int> nums;

    if (!inputFile)
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) 
    {
        nums.push_back(stoi(line));
    }

    inputFile.close();

    solve(nums);
}
