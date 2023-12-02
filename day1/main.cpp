#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <numeric>

std::pair<std::string, std::string> replace[] = {
    {"one", "one1one"},
    {"two", "two2two"},
    {"three", "three3three"},
    {"four", "four4four"},
    {"five", "five5five"},
    {"six", "six6six"},
    {"seven", "seven7seven"},
    {"eight", "eight8eight"},
    {"nine", "nine9nine"}
};

void highlightDigits(std::string& str) {
    for (auto rep : replace) {
        std::regex regex(rep.first);
        str = std::regex_replace(str, regex, rep.second);
    }
}

int findNums(const std::string& str) {
    char first, second;

    for (int i = 0; i < str.size(); ++i) {
        if (std::isdigit(str[i])) {
            first = str[i];
            break;
        }
    }

    for (int i = str.size() - 1; i > -1; --i) {
        if (std::isdigit(str[i])) {
            second = str[i];
            break;
        }
    }
    
    int a = (first - '0') * 10;
    int b = second - '0';
    return a + b;
}

int main() {
    std::ifstream fin;
    fin.open("/root/AdventOfCode2023/day1/input.txt");

    if (fin.is_open()) {
        std::vector<int> arr1, arr2;
        
        for (std::string str; std::getline(fin, str);) {
            arr1.push_back(findNums(str));

            highlightDigits(str);
            arr2.push_back(findNums(str));
        }

        std::cout << "Day 1, Part 1: " << std::accumulate(arr1.begin(), arr1.end(), 0) << std::endl;
        std::cout << "Day 1, Part 2: " << std::accumulate(arr2.begin(), arr2.end(), 0) << std::endl;
    } else {
        std::cout << "Something wrong :(" << std::endl;
    }
    fin.close();
    return 0;
}
