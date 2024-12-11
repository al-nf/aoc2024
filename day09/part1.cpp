#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream fp(argv[1]);
    if (!fp) {
        cerr << "error opening file" << endl;
        return 1;
    }

    string input;
    fp >> input;

    vector<int> data;
    vector<int> emptyIndices;
    int id = 0;            
    unsigned long long sum = 0;
    
    int empty = -1;

    for (size_t i = 0; i < input.size(); i++) 
    {
        int value = input[i] - '0';

        if (i % 2 == 0) 
        {
            int fileLength = value;

            for (int j = 0; j < fileLength; j++) 
            {
                data.push_back(id);
            }
            id++; 

        } 
        else 
        {
            int freeSpace = value;
            for (int j = 0; j < freeSpace; j++) 
            {
                data.push_back(-1);
                emptyIndices.push_back(data.size() - 1);
            }
        }
    }

    for (int i = data.size() - 1; i >= 0; i--) 
    {
        if (data[i] != -1 && !emptyIndices.empty()) 
        {
            if (emptyIndices.front() < i) 
            {
                empty = emptyIndices.front();
                data[empty] = data[i];      
                data[i] = -1;              
                emptyIndices.erase(emptyIndices.begin()); 
            }
        }
    }

    for (int i = 0; i < data.size(); i++) 
    {
        if (data[i] != -1) 
        {
            sum += static_cast<unsigned long long>(i) * static_cast<unsigned long long>(data[i]);
        }
    }

    cout << "sum: " << sum << endl;
}

