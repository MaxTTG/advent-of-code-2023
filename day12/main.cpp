#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

std::map<std::pair<std::string, std::vector<int>>, long> cache;

std::vector<std::pair<std::string, std::vector<int>>> parseSprings(std::string path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Something wrong :(" << std::endl;
        throw 1;
    }
    std::vector<std::pair<std::string, std::vector<int>>> springs;
    for (std::string str; std::getline(fin, str);) {
        for (auto& ch : str)
            if (ch == ',') ch = ' ';
        std::pair<std::string, std::vector<int>> temp;
        std::istringstream iss(str);
        iss >> temp.first;
        for (int n; iss >> n;)
            temp.second.push_back(n);
        springs.push_back(temp);
    }
    fin.close();
    return springs;
}

long countArrangements(std::string str, std::vector<int> vec) {
    if (str.empty())
        return vec.empty();

    if (vec.empty())
        return std::count(str.begin(), str.end(), '#') == 0;

    auto key = std::make_pair(str, vec);

    if (cache.find(key) != cache.end())
        return cache[key];

    long result = 0;

    if (str[0] == '.' || str[0] == '?')
        result += countArrangements(str.substr(1), vec);

    if (str[0] == '#' || str[0] == '?') {
        if (
            ( vec[0] <= str.size() ) &&
            ( std::count(str.begin(), str.begin() + vec[0], '.') == .0 ) &&
            ( vec[0] == str.size() || str[vec[0]] != '#' )
        ) {
            std::string tstr = ((vec[0] + 1) >= str.size()) ? "" : str.substr(vec[0] + 1);
            result += countArrangements(tstr, std::vector<int>(vec.begin() + 1, vec.end()));
        }
    }

    cache[key] = result;
    return result;
}

long solution(std::vector<std::pair<std::string, std::vector<int>>> springs) {
    long ans = 0;
    for (auto& spring : springs) {
        auto temp = countArrangements(spring.first, spring.second);
        ans += temp;
    }
    return ans;
}

std::vector<std::pair<std::string, std::vector<int>>> multInput(std::vector<std::pair<std::string, std::vector<int>>> springs) {
    for (auto& s : springs) {
        std::string ts(s.first);
        std::vector<int> tv(s.second);
        for (int i = 0; i < 4; ++i) {
            s.first += '?' + ts;
            for (auto tvt : tv)
                s.second.push_back(tvt);
        }
    }
    return springs;
}


int main(){
    std::string path = "/root/AdventOfCode2023/day12/input.txt";
    auto springs = parseSprings(path);
    auto ans1 = solution(springs);
    auto springs_mult = multInput(springs);
    auto ans2 = solution(springs_mult);
    std::cout << ans1 << std::endl;
    std::cout << ans2 << std::endl;
    std::cout << cache.size() << std::endl;
}
