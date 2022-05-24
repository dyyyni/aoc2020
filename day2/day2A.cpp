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

int charFrequency(std::string str, char checkChar) {
    int count{0};

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == checkChar) {
            ++count;
        }
    }

    return count;
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
        int min{std::stoi(match.str(0))};

        std::regex_search(policy, match, maxRegex);
        int max{std::stoi(match.str(0))};

        std::regex_search(policy, match, charRegex);
        std::string c{match.str(0)};

        std::regex_search(policy, match, passwordRegex);
        std::string password{match.str(0)};

        int charFreq = charFrequency(password, c[0]);
        if ( (charFreq >= min) & (charFreq <= max) ) {
            ++passwordValidyCount;
        }
    }

    std::cout << passwordValidyCount << std::endl;
}