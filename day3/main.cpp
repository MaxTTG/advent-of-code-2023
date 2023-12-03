#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <regex>
#include <numeric>

std::regex numPattern("\\d+");
std::regex starPattern("\\*");

inline bool isDot(char ch) { return ch == '.'; }

inline bool isGear(char ch) { return ch == '*'; }

std::vector<std::string> readMap(std::ifstream& fin) {
    std::vector<std::string> engineMap;
    engineMap.push_back(std::string(""));
    for (std::string str; fin >> str;)
        engineMap.push_back('.' + str + '.');
    for (int i = 0; i < engineMap[1].size(); ++i)
        engineMap[0] += '.';
    engineMap.push_back(engineMap[0]);

    return engineMap;
}

int findFullNum(std::string str, int index) {
    while(isdigit(str[--index]));
    std::string temp = str.substr(index);
    return std::stoi(str.substr(index + 1));
}

std::vector<int> engineParts(const std::vector<std::string>& engineMap) {
    std::vector<int> parts;
    for (int i = 1; i < engineMap[0].size() - 1; ++i) {
        std::string mapLine = engineMap[i];
        std::sregex_iterator start(mapLine.begin(), mapLine.end(), numPattern);
        std::sregex_iterator end;
        for (auto it = start; it != end; ++it)
        {
            std::smatch match = *it;
            int index = match.position();
            int len = match.length();
            bool flag = true;
            for (int j = index - 1; j < index + len + 1; ++j) {
                flag &= isDot(engineMap[i - 1][j]);
                flag &= isDot(engineMap[i + 1][j]);
            }
            flag &= isDot(engineMap[i][index - 1]);
            flag &= isDot(engineMap[i][index + len]);
            if (!flag)
                parts.push_back(std::stoi(match.str()));
        }
    }
    return parts;
}

std::vector<int> engineGears(const std::vector<std::string>& engineMap) {
    std::vector<int> gears;
    for (int i = 1; i < engineMap[0].size() - 1; ++i)
    {
        std::string mapLine = engineMap[i];
        std::sregex_iterator start(mapLine.begin(), mapLine.end(), starPattern);
        std::sregex_iterator end;
        for (auto it = start; it != end; ++it) {
            int firstGear = 0, secondGear = 0;
            std::smatch match = *it;
            int index = match.position();
            bool status = false;
            for (int j = -1; j < 2; ++j) {
                for (int k = -1; k < 2; ++k) {
                    if (isdigit(engineMap[i + j][index + k])) {
                        if (!status) {
                            status = true;
                            if (!firstGear)
                                firstGear = findFullNum(engineMap[i + j], index + k);
                            else
                                secondGear = findFullNum(engineMap[i + j], index + k);
                        }
                    } else status = false;
                }
                status = false;
            }
            gears.push_back(firstGear * secondGear);
        }
    }
    return gears;
}

int main(){
    std::ifstream fin;
    fin.open("/root/AdventOfCode2023/day3/input.txt");
    if (fin.is_open())
    {
        int sumParts = 0, sumGears = 0;
        auto engineMap = readMap(fin);
        auto parts = engineParts(engineMap);
        auto gears = engineGears(engineMap);
        
        sumParts = std::accumulate(parts.begin(), parts.end(), 0);
        sumGears = std::accumulate(gears.begin(), gears.end(), 0);
        std::cout << "Day 3, Part 1: " << sumParts << std::endl;
        std::cout << "Day 3, Part 2: " << sumGears << std::endl;
        
    } else {
        std::cout << "Something wrong :(" << std::endl;
    }
    fin.close();
    return 0;
}
