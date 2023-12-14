#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

std::vector<std::string> parseMap(std::string path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Something wrong :(" << std::endl;
        throw 1;
    }
    std::vector<std::string> map;
    for (std::string str; std::getline(fin, str);)
        map.push_back(str);

    fin.close();
    return map;
}

int part1(const std::vector<std::string>& map) {
    std::vector<std::vector<int>> rocks;
    int load = 0;
    for (int j = 0; j < map[0].size(); ++j) {
        int curpos = 0;
        std::vector<int> rockpos;
        for (int i = 0; i < map.size(); ++i) {
            if (map[i][j] == 'O')
                rockpos.push_back(curpos++);
            if (map[i][j] == '#')
                curpos = i + 1;
        }
        rocks.push_back(rockpos);
    }
    for (auto col : rocks) {
        for (auto rock : col) {
            load += map.size() - rock;
        }
    }
    return load;
}

int load(const std::vector<std::string>& map) {
    int ans = 0;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            if (map[i][j] == 'O')
                ans += map.size() - i;
        }
    }
    return ans;
}

int part2(std::vector<std::string> map, int totalcycles = 1'000'000'000) {
    std::map<std::vector<std::string>, int> maps;
    int firstcycle = 0, repeatedcycle = 0;
    for (int cycle = 0; cycle < totalcycles; ++cycle) {
        // up
        for (int j = 0; j < map[0].size(); ++j) {
            int curpos = 0;
            for (int i = 0; i < map.size(); ++i) {
                if (map[i][j] == 'O') {
                    map[i][j] = '.';
                    map[curpos++][j] = 'O';
                }
                if (map[i][j] == '#') {
                    curpos = i + 1;
                }
            }
        }
        // left
        for (int i = 0; i < map.size(); ++i) {
            int curpos = 0;
            for (int j = 0; j < map[0].size(); ++j) {
                if (map[i][j] == 'O') {
                    map[i][j] = '.';
                    map[i][curpos++] = 'O';
                }
                if (map[i][j] == '#') {
                    curpos = j + 1;
                }
            }
        }
        // down
        for (int j = 0; j < map[0].size(); ++j) {
            int curpos = map.size() - 1;
            for (int i = map.size() - 1; i >= 0; --i) {
                if (map[i][j] == 'O') {
                    map[i][j] = '.';
                    map[curpos--][j] = 'O';
                }
                if (map[i][j] == '#') {
                    curpos = i - 1;
                }
            }
        }
        // right
        for (int i = 0; i < map.size(); ++i) {
            int curpos = map[0].size() - 1;
            for (int j = map[0].size() - 1; j >= 0; --j) {
                if (map[i][j] == 'O') {
                    map[i][j] = '.';
                    map[i][curpos--] = 'O';
                }
                if (map[i][j] == '#') {
                    curpos = j - 1;
                }
            }
        }
        // cycle end
        std::cout << load(map) << ' ';
        if (auto f = maps.find(map); f != maps.end()) {
            std::cout << "FIND!!!" << std::endl;
            repeatedcycle = cycle;
            firstcycle = f->second;
            break;
        } else {
            maps.emplace(map, cycle);
        }
    }
    if (firstcycle && repeatedcycle) {
        repeatedcycle -= firstcycle;
        totalcycles -= firstcycle;
        firstcycle = 0;
        int cyclesneed = totalcycles % repeatedcycle;
        return part2(map, cyclesneed - 1);
    } else {
        return load(map);
    };
}

int main(){
    std::string path = "/root/AdventOfCode2023/day14/input.txt";
    auto map = parseMap(path);
    int ans1 = part1(map);
    int ans2 = part2(map);
    std::cout << "\nDay 14, Part 1: " << ans1 << std::endl;
    std::cout << "Day 14, Part 2: " << ans2 << std::endl;
}
