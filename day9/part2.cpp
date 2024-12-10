#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

std::vector<int> readInput(const std::string& filename) {
    std::vector<int> nums;
    std::ifstream file(filename);
    char c;

    while (file >> c) {
        nums.push_back(c - '0');
    }
    
    return nums;
}


void part2(const std::vector<int>& n) {
    std::vector<int> blocksize;
    std::vector<int> disk;
    std::vector<int> b_pos;

    for (size_t i = 0; i < n.size(); ++i) {
        if (i % 2 == 0) {
            blocksize.push_back(n[i]);
            b_pos.push_back(disk.size());
            for (int j = 0; j < n[i]; ++j) {
                disk.push_back(blocksize.size() - 1);
            }
        } else {
            for (int j = 0; j < n[i]; ++j) {
                disk.push_back(-1);
            }
        }
    }

    for (size_t i = blocksize.size() - 1; i > 0; --i) {
        int empty = 0;
        int start = 0;

        for (size_t j = 0; j < disk.size(); ++j) {
            if (j >= b_pos[i]) break;

            if (disk[j] < 0) {
                empty++;
                if (empty == 1) {
                    start = j;
                }
            } else {
                empty = 0;
            }

            if (empty >= blocksize[i]) {
                for (int k = 0; k < blocksize[i]; ++k) {
                    disk[start + k] = i;
                    disk[b_pos[i] + k] = -1;
                }
                break;
            }
        }
    }

    unsigned long long ans = 0;
    for (size_t i = 0; i < disk.size(); ++i) {
        if (disk[i] < 0) continue;
        ans += i * disk[i];
    }
    
    std::cout << ans << std::endl;
}

int main() {
    std::string filename = "input.txt";
    std::vector<int> nums = readInput(filename);
    
    part2(nums); 

    return 0;
}

