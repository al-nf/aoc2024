#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

void solve(const vector<int>& nums)
{
    ULL sum = 0;

    for (int num : nums)
    {
        int res = num;
        for (int i = 0; i < 2000; i++)
        {
            res = calc(res);
        }
        sum += res;
    }
    printf("sum: %llu\n", sum);
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
