#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bit>

std::vector<std::vector<std::string>> parseMaps(const std::string & path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Something wrong :(" << std::endl;
        throw 1;
    }
    std::vector<std::vector<std::string>> maps;
    std::vector<std::string> map;
    for (std::string str; std::getline(fin, str);) {
        if (str != "") {
            map.push_back(str);
        } else {
            maps.push_back(map);
            map.clear();
        }
    }
    maps.push_back(map);
    fin.close();
    return maps;
}

int beforeMirror(const std::vector<uint32_t>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        bool isMirror = true;
        for (int j = 1; i + 1 >= j && i + j < vec.size(); ++j) {
            if (vec[i + j] != vec[i - j + 1]) {
                isMirror = false;
                break;
            }
        }
        if (isMirror)
            return i + 1;
    }
    throw -1;
}

int beforeSmudgeMirror(const std::vector<uint32_t>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        bool isMirror = true;
        bool isSmudge = false;
        for (int j = 1; i + 1 >= j && i + j < vec.size(); ++j) {
            if (std::__popcount(vec[i + j] ^ vec[i - j + 1]) == 1 && !isSmudge) {
                isSmudge = true;
            } else if (vec[i + j] != vec[i - j + 1]) {
                isMirror = false;
                break;
            } 
        }
        if (isMirror && isSmudge)
            return i + 1;
    }
    return vec.size();
}

int solution(const std::vector<std::vector<std::string>>& maps, int mirrorfunc(const std::vector<uint32_t>&)) {
    int rbefore = 0;
    int cbefore = 0;
    for (auto map : maps) {
        std::vector<uint32_t> rows;
        std::vector<uint32_t> cols;

        for (int i = 0; i < map.size(); ++i) {
            uint32_t horindex = 0;
            for (int j = 0; j < map[i].size(); ++j) {
                horindex += (map[i][j] == '#');
                horindex = horindex << 1;
            }
            rows.push_back(horindex);
        }
        for (int j = 0; j < map[0].size(); ++j) {
            uint32_t vertindex = 0;
            for (int i = 0; i < map.size(); ++i) { 
                vertindex += (map[i][j] == '#');
                vertindex = vertindex << 1;
            }
            cols.push_back(vertindex);
        }
        int rindex = mirrorfunc(rows);
        int cindex = mirrorfunc(cols);

        rbefore += ( rindex == map.size() ) ? 0 : rindex;
        cbefore += ( cindex == map[0].size() ) ? 0 : cindex;
    }
    
    return rbefore * 100 + cbefore;
}



int main() {
    std::string path = "/root/AdventOfCode2023/day13/input.txt";
    auto maps = parseMaps(path);
    std::cout << solution(maps, beforeMirror) << std::endl;
    std::cout << solution(maps, beforeSmudgeMirror) << std::endl;
}
