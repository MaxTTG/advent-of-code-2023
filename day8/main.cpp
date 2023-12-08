#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <numeric>

std::pair<std::string, std::unordered_map<std::string, std::pair<std::string, std::string>>> parseMap(std::string path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Something wrong :(" << std::endl;
        throw 1;
    }
    std::string map;
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodesnw;
    std::getline(fin, map);
    char eq;
    std::string key, left, right;
    while (fin >> key >> eq >> left >> right) {
        left.erase(left.begin());
        left.erase(left.end() - 1);
        right.erase(right.end() - 1);
        nodesnw[key] = std::pair(left, right);
    }
    return {map, nodesnw};
}

int part1(std::string map, std::unordered_map<std::string, std::pair<std::string, std::string>> nw, std::string key = "AAA") {
    int ans = 1;
    char way;
    for (short i = 0; ans > 0; ++ans, ++i ) {
        if (i == map.size()) i = 0;
        way = map[i];
        auto pair = nw[key];
        key = way == 'L' ? pair.first : pair.second;
        if (key == "ZZZ")
            return ans;
    }
    return -1;
}

long long part2(std::string map, std::unordered_map<std::string, std::pair<std::string, std::string>> nw) {
    std::set<std::string> allkeys;
    std::vector<std::string> keys;
    std::vector<int> cycles;

    for (auto node : nw) {
        allkeys.insert(node.first);
        allkeys.insert(node.second.first);
        allkeys.insert(node.second.second);
    }

    for (auto key : allkeys)
        if (key[2] == 'A')
            keys.push_back(key);

    for (auto key : keys) {
        int i = 0;
        int ans = 1;
        char way;
        for (int i = 0; ans > 0; ++ans, ++i ) {
            if (i == map.size()) i = 0;
            way = map[i];
            auto pair = nw[key];
            key = way == 'L' ? pair.first : pair.second;
            if (key[2] == 'Z') break;
        }
        cycles.push_back(ans);
    }

    int64_t c = cycles[0];
    cycles.erase(cycles.begin());

    for (auto cycle : cycles)
        c = c * cycle / std::gcd(c, cycle);

    return c;
}

int main(int, char**){
    std::string path = "/root/AdventOfCode2023/day8/input.txt";
    auto [map, nw] = parseMap(path);
    std::cout << "Day 8, Part 1: " << part1(map, nw) << std::endl;
    std::cout << "Day 8, Part 2: " << part2(map, nw) << std::endl;
    return 0;
}
