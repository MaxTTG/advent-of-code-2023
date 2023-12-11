#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

#include <ctime>

std::vector<std::string> parseSky(std::string path) {
    std::vector<std::string> sky;
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Something wrong :(" << std::endl;
        throw 1;
    }
    std::string temp;
    while (std::getline(fin, temp))
        sky.push_back(temp);
    return sky;
}

std::pair<std::set<int>, std::set<int>> findSpace(const std::vector<std::string>& sky) {
    std::set<int> rows;
    std::set<int> cols;
    // rows
    for (int i = 0; i < sky.size(); ++i) {
        bool flag = true;
        for (int j = 0; j < sky[0].size(); ++j)
            flag &= sky[i][j] == '.';
        if (flag)
            rows.insert(i);
    }

    // cols
    for (int j = 0; j < sky.size(); ++j) {
        bool flag = true;
        for (int i = 0; i < sky[0].size(); ++i)
            flag &= sky[i][j] == '.';
        if (flag)
            cols.insert(j);
    }
    return std::make_pair(rows, cols);
}

long space(const std::vector<std::string>& sky, int scale) {
    int num = 0;
    long ans = 0;
    auto [rows, cols] = findSpace(sky);
    std::map<int, std::pair<int, int>> galaxies;
    
    for (int i = 0; i < sky.size(); ++i)
        for (int j = 0; j < sky[i].size(); ++j)
            if (sky[i][j] == '#')
                galaxies[num++] = std::make_pair(i, j);

    for (int i = 0; i < num; ++i) {
        for (int j = i + 1; j < num; ++j) {
            auto [x1, y1] = galaxies[i];
            auto [x2, y2] = galaxies[j];
            int xmin = std::min(x1, x2), xmax = std::max(x1, x2);
            int ymin = std::min(y1, y2), ymax = std::max(y1, y2);
            /*
            // NonOptimised time: 3.50543
            for (int xx = xmin; xx < xmax; ++xx)
                ans += (rows.find(xx) == rows.end()) ? 1 : scale;
            for (int yy = ymin; yy < ymax; ++yy)
                ans += (cols.find(yy) == cols.end()) ? 1 : scale;
            */
            // Optimised time: 0.351872
            auto itx1 = rows.upper_bound(xmin);
            auto itx2 = rows.lower_bound(xmax);
            auto ity1 = cols.upper_bound(ymin);
            auto ity2 = cols.lower_bound(ymax);
            int rownum = std::distance(itx1, itx2);
            int colnum = std::distance(ity1, ity2);
            int dx = xmax - xmin - rownum, dy = ymax - ymin - colnum;
            ans += dx + dy + (rownum + colnum) * scale;
        }
    }
    return ans;
}

int main(int, char**){
    std::string path = "/root/AdventOfCode2023/day11/input.txt";
    auto sky = parseSky(path);
    unsigned int start_time =  clock();

    std::cout << space(sky, 2) << std::endl;
    std::cout << space(sky, 1000000) << std::endl;
    
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    std::cout << "Time: " << (float) search_time / CLOCKS_PER_SEC << std::endl;
}
//9723824
//731244261352
