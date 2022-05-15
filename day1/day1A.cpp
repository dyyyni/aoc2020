#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool fileReader(std::string fileName, std::vector<int>& nums) {
    std::ifstream ifile{fileName};
    if (!ifile) {
        std::cout << "File " << fileName << " could not be opened.";
        return false;
    }
    std::string str; 

    while (std::getline(ifile, str)) {
        if (str.size() > 0) nums.push_back(std::stoi(str));
    }

    ifile.close();
    return true;
    
}

int main() {
    std::vector<int> nums;
    std::string fileName{"input.txt"};

    bool result = fileReader(fileName, nums);

    if (result) {
        for(auto num : nums) {
            if (num > 1000) continue;
            else {
                for (auto num2 : nums) {
                    if (num + num2 == 2020) {
                        std::cout << num * num2 << std::endl;
                        break;
                        }
                }
            }
        }
    }
}