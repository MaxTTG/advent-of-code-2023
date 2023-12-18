#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <tuple>

typedef std::tuple<int, int, int, int, int> t5;
typedef std::tuple<int, int, int, int, int, int> t6;

struct ComparatorT{bool operator() (const t6& a, const t6& b){return a > b;}};

std::vector<std::vector<int>> parseInput(std::string path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Something wrong :(\n";
        throw 1;
    }
    std::vector<std::vector<int>> input;
    for (std::string str; std::getline(fin, str);) {
        std::istringstream iss(str);
        std::vector<int> temp;
        for (char ch; iss.get(ch);)
            temp.push_back(ch - '0');
        input.push_back(temp);
    }
    fin.close();
    return input;
}

int part1(const std::vector<std::vector<int>>& input) {
    std::priority_queue<t6, std::vector<t6>, ComparatorT> pq;
    pq.push({0, 0, 0, 0, 0, 0});
    std::set<t5> seen;
    std::vector<std::pair<int, int>> moves{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while (!pq.empty()) {
        auto [cost, x, y, dx, dy, n] = pq.top(); pq.pop();
        if (x == input.size() - 1 && y == input[0].size() - 1)
            return cost;
        
        if (seen.count({x, y, dx, dy, n}) > 0)
            continue;
        
        seen.insert({x, y, dx, dy, n});

        if (n < 3 && (dx != 0 || dy != 0)) {
            auto nx = x + dx;
            auto ny = y + dy;
            if (0 <= nx && nx < input.size() && 0 <= ny && ny < input[0].size()) 
                pq.push({cost + input[nx][ny], nx, ny, dx, dy, n + 1});
        }

        for ( auto [ndx, ndy] : moves) {
            if ((ndx != dx || ndy != dy) && (ndx != -dx || ndy != -dy)) {
                int nx = x + ndx;
                int ny = y + ndy;
                if (0 <= nx && nx < input.size() && 0 <= ny && ny < input[0].size())
                    pq.push({cost + input[nx][ny], nx, ny, ndx, ndy, 1});
            }
        }
    }
    throw 1;
}

int part2(const std::vector<std::vector<int>>& input) {
    std::priority_queue<t6, std::vector<t6>, ComparatorT> pq;
    pq.push({0, 0, 0, 0, 0, 0});
    std::set<t5> seen;
    std::vector<std::pair<int, int>> moves{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while (!pq.empty()) {
        auto [cost, x, y, dx, dy, n] = pq.top(); pq.pop();
        if (x == input.size() - 1 && y == input[0].size() - 1 && n >= 4)
            return cost;
        
        if (seen.count({x, y, dx, dy, n}) > 0)
            continue;
        
        seen.insert({x, y, dx, dy, n});

        if (n < 10 && (dx != 0 || dy != 0)) {
            auto nx = x + dx;
            auto ny = y + dy;
            if (0 <= nx && nx < input.size() && 0 <= ny && ny < input[0].size()) 
                pq.push({cost + input[nx][ny], nx, ny, dx, dy, n + 1});
        }

        if (n >= 4 || (dx == 0 && dy == 0)) {
            for ( auto [ndx, ndy] : moves) {
                if ((ndx != dx || ndy != dy) && (ndx != -dx || ndy != -dy)) {
                    int nx = x + ndx;
                    int ny = y + ndy;
                    if (0 <= nx && nx < input.size() && 0 <= ny && ny < input[0].size())
                        pq.push({cost + input[nx][ny], nx, ny, ndx, ndy, 1});
                }
            }
        }
    }
    throw 1;
}

int main() {
    std::string path("/root/AdventOfCode2023/day17/input.txt");
    auto map = parseInput(path);
    std::cout << part1(map) << std::endl;
    std::cout << part2(map) << std::endl;
}
// 
// 