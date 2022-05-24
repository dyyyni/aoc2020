#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

void readData(std::vector<std::string>& strVec) {
    std::ifstream ifile{"input.txt"};

    if(!ifile) {
        std::cout << "File not found" << std::endl;
        return;
    }

    std::string str;
    while (std::getline(ifile, str)) {
        if (std::size(str) > 0) strVec.push_back(str);
    }
    ifile.close();
    return;
}

int main() {
    std::vector<std::string> passwordPolicy;
    readData(passwordPolicy);

    std::regex minRegex(R"(\d+?(?=-))");
    std::regex maxRegex(R"(\d+?(?=\s))");
    std::regex charRegex(R"(\w+?(?=:))");
    std::regex passwordRegex(R"([^:\s]*$)");

    int passwordValidyCount = 0;

    for (auto policy : passwordPolicy) {
        std::smatch match;

        std::regex_search(policy, match, minRegex);
        int firstPos{std::stoi(match.str(0))};

        std::regex_search(policy, match, maxRegex);
        int lastPos{std::stoi(match.str(0))};

        std::regex_search(policy, match, charRegex);
        std::string c{match.str(0)};

        std::regex_search(policy, match, passwordRegex);
        std::string password{match.str(0)};

        // The client does not adhere to index zero.
        if ( (c[0] == password[firstPos - 1]) | (c[0] == password[lastPos - 1]) ) {
            if (password[firstPos - 1] != password[lastPos - 1] ) {
                ++passwordValidyCount;
            }
        } 
    }

    std::cout << passwordValidyCount << std::endl;
}