#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <stack>

struct Almanac {
    struct AlmanacMap {
        struct AlmanacString {
            AlmanacString(long f, long s, long i) : from(s), to(f), len(i) {}
            long from;
            long to;
            long len;
        };
        
        AlmanacMap() = default;

        void add(std::string str) {
            std::istringstream iss(str);
            long f, s, i;
            iss >> f >> s >> i;
            map.push_back(AlmanacString(f, s, i));
        }
        
        long findLower(long key) {
            long val = INT32_MAX;
            for (auto str : map)
                if (str.from <= key && key < str.from + str.len)
                    val = str.to + (key - str.from);
            
            if (val == INT32_MAX)
                return key;
            return val;
        }

        std::vector<AlmanacString> map;
    };

    Almanac(std::string& path) {
        std::ifstream fin(path);
        if (fin.is_open()) {
            std::string seed;
            fin >> seed; // "seeds:"
            while (fin >> seed) {
                seeds.push_back(std::stol(seed));
                if (fin.peek() == '\n')
                    break;
            }

            int mapid = -1;
            for (std::string str; getline(fin, str);) {
                if (str.empty()) continue;
                if (isalpha(str[0])) {
                    ++mapid;
                    maps.push_back(Almanac::AlmanacMap());
                    continue;
                }
                maps[mapid].add(str);
            }
        } else {
            std::cerr << "Cannot read Almonac from current path" << std::endl;
            throw -1;
        }
    }

    long findLocation(const long& seed) {
        long ans = seed;
        for (auto map : maps)
            ans = map.findLower(ans);
        return ans;
    }

    long lowerLocation() {
        long location = INT64_MAX;
        for (auto seed : seeds) {
            long temp = findLocation(seed);
            if (temp < location)
                location = temp;
        }
        return location;
    }
    
    long lowerLocation2() {
        std::stack<std::pair<long, long>> seeds_ranges;
        for (int i = 0; i < seeds.size(); ++i) {
            int f = i, s = ++i;
            seeds_ranges.push(std::pair<long, long>(seeds[f], seeds[f] + seeds[s]));
        }
        for (auto m : maps) {
            std::stack<std::pair<long, long>> neww;
            while (!seeds_ranges.empty()) {
                auto se = seeds_ranges.top();
                seeds_ranges.pop();
                bool flag = true;
                for (auto range : m.map) {
                    long os = std::max(se.first, range.from);
                    long oe = std::min(se.second, range.from + range.len);
                    if (os < oe) {
                        neww.push(std::pair(os - range.from + range.to, oe - range.from + range.to));
                        if (os > se.first)
                            seeds_ranges.push(std::pair(se.first, os));
                        if (se.second > oe) 
                            seeds_ranges.push(std::pair(oe, se.second));
                        flag = false;
                        break;
                    }
                }
                if (flag)
                    neww.push(std::pair(se.first, se.second));
            }
            seeds_ranges = neww;
        }
        std::vector<std::pair<long, long>> sr;
        while (!seeds_ranges.empty()) {
            sr.push_back(seeds_ranges.top());
            seeds_ranges.pop();
        }
        std::sort(sr.begin(), sr.end());
        return sr[0].first;
    }

    std::vector<AlmanacMap> maps;
    std::vector<long> seeds;
};

int main(){
    std::string path("/root/AdventOfCode2023/day5/input.txt");
    Almanac almanac(path);

    long lowerLoc = almanac.lowerLocation();
    std::cout << "Day 5, Part 1: " << lowerLoc << std::endl;
    
    long lowerLoc2 = almanac.lowerLocation2();
    std::cout << "Day 5, Part 2: " << lowerLoc2 << std::endl;
    
    return 0;
}
