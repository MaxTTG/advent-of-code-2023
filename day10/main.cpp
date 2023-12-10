#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <set>

std::map<char, std::vector<int>> guide = {
    // up, right, left down
    {'S', {1, 1, 1, 1}},
    {'-', {0, 1, 1, 0}},
    {'|', {1, 0, 0, 1}},
    {'L', {1, 1, 0, 0}},
    {'J', {1, 0, 1, 0}},
    {'7', {0, 0, 1, 1}},
    {'F', {0, 1, 0, 1}},
    {'.', {0, 0, 0, 0}}
};

std::tuple<std::vector<std::string>, int, int> parseMap(std::string path) {
    std::vector<std::string> map;
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Simething wrong :(" << std::endl;
        throw 1;
    }
    for (std::string str; std::getline(fin, str); map.push_back(str));
    for (int y = 0; y < map.size(); ++y)
        for (int x = 0; x < map[y].size(); ++x)
            if (map[y][x] == 'S')
                return { map, x, y };
    throw 1;
}

std::pair<int, int> checkNext(char next, int dx, int dy) {
    auto a = guide[next];
    if (dx == 1)
        a[2] = 0;
    else if (dx == -1)
        a[1] = 0;
    else if (dy == 1)
        a[0] = 0;
    else if (dy == -1)
        a[3] = 0;
    return std::make_pair(a[1] - a[2], a[3] - a[0]);
}

std::pair<int, std::set<std::pair<int, int>>> part1(std::vector<std::string>& map, const int& xx, const int& yy) {
    if (map[yy][xx] != 'S') throw 1;
    std::set<std::pair<int, int>> cells;
    for (int starty = -1; starty < 2; ++starty) for (int startx = -1; startx < 2; ++startx) {
        if ((starty + startx) % 2 == 0 ) continue;
        auto x = xx, y = yy, stepcounter = 0;
        auto move = std::make_pair(startx, starty);
        bool correct = true;
        cells.clear();
        while (correct) {
            ++stepcounter;
            x += move.first;
            y += move.second;
            char next = map[y][x];
            if (next == 'S')
                break;
            cells.insert(std::make_pair(x, y));
            move = checkNext(next, move.first, move.second);
            correct &= (abs(move.first + move.second) == 1);
        }
        if (correct) {
            return std::make_pair(stepcounter / 2, cells);
        }
    }
    throw 1;
}

int part2(std::vector<std::string> map, std::set<std::pair<int, int>> path) {
    bool inn = false;
    int count = 0;
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (path.find(std::make_pair(x, y)) != path.end()) {
                if (map[y][x] == '7' || map[y][x] == 'F' || map[y][x] == '|')
                    inn = !inn;
            } else 
                count += inn;
        }
    }
    return count;
}

int main(){
    std::string path = "/root/AdventOfCode2023/day10/input.txt";
    auto [map, x, y] = parseMap(path);
    auto [ans1, way] = part1(map, x, y);
    auto ans2 = part2(map, way);
    std::cout << ans1 << std::endl;
    std::cout << ans2 << std::endl;
}
