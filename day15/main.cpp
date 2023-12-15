#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <list>

class Box {
public:
    Box() : names(), lens() {};
    void add(std::string key, int num) {
        names.push_back(key);
        lens.emplace(key, num);
    }
    void add_or_change(std::string key, int num) {
        auto it = lens.find(key);
        if (it != lens.end())
            it->second = num;
        else add(key, num);
    }
    void remove(std::string key) {
        if (lens.find(key) != lens.end()) {
            names.remove(key);
            lens.erase(key);
        }
    }
    int size() {
        return names.size();
    }
    std::pair<std::string, int> operator[] (int i) {
        std::string key = *std::next(names.begin(), i);
        return std::make_pair(key, lens[key]);
    }
private:
    std::list<std::string> names;
    std::map<std::string, int> lens;
};

std::vector<std::string> parseInput(std::string path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Something wrong :(\n";
        throw 1;
    }
    std::vector<std::string> instruction;
    for (std::string str; std::getline(fin, str, ',');)
        instruction.push_back(str);
    fin.close();
    return instruction;
}

int findHash(const std::string str) {
    int cur = 0;
    for (auto& c : str) {
        cur += (int) c;
        cur = cur + (cur << 4);
        cur &= 0b1111'1111; // cur %= 256 == cur &= (256 - 1)
    }
    return cur;
}

int part1(const std::vector<std::string>& instruction) {
    int ans = 0;
    for (auto& s : instruction)
        ans += findHash(s);
    return ans;
}

int part2(const std::vector<std::string>& instruction) {
    std::regex pattern("([a-z]+)([-]|[=](\\d))"); // "randomchars" + ("-" or "=digit")
    std::vector<Box> boxes(256, Box());
    for (auto& s : instruction) {
        std::smatch match;
        std::regex_search(s, match, pattern);

        std::string key = match[1];
        bool op = *match[2].first == '='; // true -> abc=1; false -> abc-
        int num = op ? std::stoi(match[3]) : 0;
        int i = findHash(key);
        if (op)
            boxes[i].add_or_change(key, num);
        else
            boxes[i].remove(key);
    }

    int ans = 0;
    for (int i = 0; i < boxes.size(); ++i)
        for (int j = 0; j < boxes[i].size(); ++j)
            ans += (i + 1) * (j + 1) * boxes[i][j].second;

    return ans;
}

int main() {
    std::string path("/root/AdventOfCode2023/day15/input.txt");
    auto instructions = parseInput(path);
    std::cout << part1(instructions) << std::endl;
    std::cout << part2(instructions) << std::endl;
}
// 511416
// 290779