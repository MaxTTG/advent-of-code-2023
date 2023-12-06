#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::pair<int, int>> parseRaces(const std::string& path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Something wrong :(" << std::endl;
        throw 1;
    }
    std::vector<std::vector<int>> temp;
    std::vector<std::pair<int, int>> races;
    for (std::string str; std::getline(fin, str);) {
        std::vector<int> t;
        std::istringstream iss(str);
        iss >> str;
        while (iss >> str)
            t.push_back(std::stoi(str));
        temp.push_back(t);
    }
    for (int i = 0; i < temp[0].size(); ++i) {
        races.push_back(std::pair(temp[0][i], temp[1][i]));
    }
    return races;
}

template <typename T>
std::enable_if_t<std::is_integral_v<T>, T>
numOfTimes(std::pair<T, T> race) {
    T count = 0;
    T Time = race.first;
    T Len = race.second;
    for (T t = 1; t < Time; ++t) {
        if ((Time - t) * t > Len)
            ++count;
    }
    return count;
}

std::pair<int64_t, int64_t> bkInput(std::vector<std::pair<int, int>> races) {
    std::string str1 = "", str2 = "";
    for (auto t : races) {
        str1 += std::to_string(t.first);
        str2 += std::to_string(t.second);
    }
    return std::pair(std::stoll(str1), std::stoll(str2));
}

int part1(std::vector<std::pair<int, int>> races) {
    int mul = 1;
    for (auto race : races)
        mul *= numOfTimes(race);
    return mul;
}

int part2(std::pair<int64_t, int64_t> race) {
    return numOfTimes(race);
}

int main(){
    std::string path("/root/AdventOfCode2023/day6/input.txt");
    auto races = parseRaces(path);
    std::cout << part1(races) << std::endl;
    auto race = bkInput(races);
    std::cout << part2(race) << std::endl;
}
