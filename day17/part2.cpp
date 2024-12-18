#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <cmath>
#include <ranges>

#define ULL unsigned long long 

using namespace std;

vector<ULL> program(vector<ULL>& registers, const vector<ULL>& instructions)
{
    ULL opcode;
    ULL operand;
    vector<ULL> out;
    for (ULL i = 0; i < instructions.size(); i += 2)
    {
        opcode = instructions[i];
        const ULL operandLit = instructions[i + 1];
        operand = instructions[i + 1];

        switch (operand)
        {
            case 4:
            {
                operand = registers[0];
                break;
            }
            case 5:
            {
                operand = registers[1];
                break;
            }
            case 6:
            {
                operand = registers[2];
                break;
            }
            default:
                break;
        }

        switch (opcode)
        {
            case 0:
            {
                registers[0] /= (1ULL << operand);
                break;
            }
            case 1:
            {
                registers[1] = registers[1] ^ operandLit;
                break;
            }
            case 2:
            {
                registers[1] = operand % 8;
                break;
            }
            case 3:
            {
                if (registers[0] != 0)
                {
                    i = operandLit;
                    i -= 2;
                }
                break;
            }
            case 4:
            {
                registers[1] = registers[1] ^ registers[2];
                break;
            }
            case 5:
            {
                out.push_back(operand % 8);
                break;
            }
            case 6:
            {
                registers[1] = registers[0] / (1ULL << operand);
                break;
            }
            case 7:
            {
                registers[2] = registers[0] / (1ULL << operand);
                break;
            }
        }
    }

    return out;
}

int main(int argc, char *argv[])
{
    ifstream inputFile(argv[1]);
    vector<ULL> registers(3, 0); 
    vector<ULL> instructions;

    if (!inputFile)
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    regex registerRegex("(Register [A-C]): (\\d+)");
    regex programRegex("Program: (.+)"); 

    while (getline(inputFile, line))
    {
        smatch match;

        if (regex_match(line, match, registerRegex))
        {
            char reg = match[1].str()[9]; 
            ULL value = stoi(match[2].str()); 
            
            if (reg == 'A')
                registers[0] = value;
            else if (reg == 'B')
                registers[1] = value;
            else if (reg == 'C')
                registers[2] = value;
        }
        else if (regex_match(line, match, programRegex))
        {
            string instructionsLine = match[1].str();
            stringstream ss(instructionsLine);
            string instruction;
            
            while (getline(ss, instruction, ','))
            {
                instructions.push_back(stoi(instruction));
            }
        }
    }
    inputFile.close();

    ULL i = 0;
    registers[0] = i;

    vector<ULL> out = program(registers, instructions);
    for (int j = instructions.size()-1; j >= 0; j--)
    {
        while (out[j] != instructions[j]) 
        {
            printf("Digit %llu is currently %llu at %llu\n", j, out[j], i);
            i += (1ULL << (3 * j)); 
            registers[0] = i;
            out = program(registers, instructions);
            for (ULL num : out)
            {
                printf("%llu ", num);
            }
            printf("A: %llu\n", i);
        }
        printf("Confirmed digit %llu to be %llu \n", j, out[j]);
    }
    
    for (ULL num : out)
    {
        printf("%llu ", num);
    }
    printf("A: %llu\n", i);
}

