#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> parse(std::string path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cout << "Something wrong :(" << std::endl;
        throw 1;
    }
    std::vector<std::vector<int>> ans;
    std::string str;
    while(std::getline(fin, str)) {
        std::vector<int> temp;
        std::istringstream iss(str);
        int t;
        while (iss >> t) temp.push_back(t); 
        ans.push_back(temp);
    }
    return ans;
}

std::vector<int> pyramid(std::vector<int> in) {
    std::vector<int> out;
    for (int i = 1; i < in.size(); ++i)
        out.push_back(in[i] - in[i - 1]);
    return out;
}

std::pair<int, int> part12(std::vector<std::vector<int>> input) {
    int ans1 = 0;
    int ans2 = 0;
    for (auto vec : input) {
        std::vector<std::vector<int>> p;
        std::vector<int> temp = vec;
        p.push_back(temp);
        while (true) {
            temp = pyramid(temp);
            p.push_back(temp);
            bool flag = true;
            for (auto t : temp)
                flag &= t == 0;
            if (flag) break;
        }
        int k = 0, m = 0;
        for (auto tt : p)
            k += tt.back();
        ans1 += k;

        for (int i = p.size() - 1; i > -1; --i)
            m = p[i][0] - m;
        ans2 += m;
    }
    return std::make_pair(ans1, ans2);
}

int main(){
    std::string path = "/root/AdventOfCode2023/day9/input.txt";
    auto input = parse(path);
    auto [ans1, ans2] = part12(input);
    std::cout << ans1 << std::endl;
    std::cout << ans2 << std::endl;
}
